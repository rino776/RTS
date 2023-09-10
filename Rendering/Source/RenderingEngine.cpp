#include "RenderingEngine.h"
#include <RenderingEngine.h>
#include <glm/ext/matrix_transform.hpp>
#include <Transform.h>

using namespace rendering;
using namespace core;

//so it looks like mutexes have to be global scope?
std::mutex g_renderingMutex;

RenderingEngine::RenderingEngine(std::shared_ptr<InputManager> inputManager) {
	m_inputManager = inputManager;
	m_shouldClose = false;
}

void RenderingEngine::init() {
	printf("Started Rendering Thread\n");
	m_windowManager = std::make_unique<WindowManager>(m_inputManager);
	m_shouldClose = !m_windowManager->createWindow(800,600,"Hello World!");
	m_renderManager = std::make_unique<RenderManager>();
	renderLoop();
}

std::thread RenderingEngine::start() {
	return std::thread(&RenderingEngine::init, this);
}

void RenderingEngine::setCameraTransform(Transform* transform) {
	std::lock_guard<std::mutex>lock(g_renderingMutex);
	if(m_renderManager)
		m_renderManager->getCamera()->setPos(transform);
}

Transform* RenderingEngine::getCameraTransform() {
	return m_renderManager->getCamera()->getTransform();
}

void RenderingEngine::renderLoop() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDisable(GL_CULL_FACE);
	while (!m_windowManager->shouldClose() && !m_shouldClose) {
		//update stuff here
		m_windowManager->updateWindow();

		if (m_windowManager->dirty()) {
			m_renderManager->getCamera()->setScreenDetails(m_windowManager->getDetails());
			m_windowManager->setDirty(false);
		}
		
		//TODO: move these into the render pass?
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		updateEntities();
		m_renderManager->renderPass();
	}
	cleanup();
}

void RenderingEngine::updateEntities() {
	std::lock_guard<std::mutex>lock(g_renderingMutex);
	for (Entity* e : m_dirtyEnts) {
		
		//we have handled the entity (or are about to I guess)
		e->setDirty(false);

		
		//we probably want to check id here as well, to see if it is a new RC or an updated one...
		//or should we always create new ones, and delete the old ones?
		RenderCommand* rc{};	
		Component* renderable;
		renderable = e->getComponent(eMesh);
		if (renderable) {
			rc = createMesh((Mesh*)renderable, e->id());
		}
		renderable = e->getComponent(eSprite);
		if (renderable) {
			rc = createSprite((Sprite*)renderable, e->id());
		}

		if (!rc)
			continue;

		Component* c = e->getComponent(eTransform);
		if (c) {	
			Transform* transform = (Transform*)(c);
			rc->setModelMatrix(transform->getTransformMatrix());
		}
	
		if(rc){
			m_renderManager->addRenderCommand(rc);
		}
	
	}

	m_dirtyEnts.clear();
}

void RenderingEngine::setDirtyEntities(std::vector<Entity*>& dirtyEnts) {
	std::lock_guard<std::mutex>lock(g_renderingMutex);
	m_dirtyEnts.insert(m_dirtyEnts.end(), dirtyEnts.begin(), dirtyEnts.end());
}

RenderCommand* RenderingEngine::createSprite(Sprite* sprite, unsigned int id) {
	float vertexArray[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,

		-0.5f,  -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	std::vector<float> vertices = std::vector<float>();
	
	vertices.insert(vertices.end(), &vertexArray[0], &vertexArray[18]);
	Geometry* geometry = new Geometry();
	geometry->addComponent(vertex, vertices);
	RenderCommand* rc = new RenderCommand(id);
	rc->setGeometry(geometry);
	return rc;
}

RenderCommand* RenderingEngine::createMesh(Mesh* mesh, unsigned int id)
{
	//get vertex and index data
	std::vector<float> vertexData = mesh->getVertexData();
	std::vector<unsigned int> indices = mesh->getIndexData();
	std::vector<unsigned int> normalIndices = mesh->getNormalIndexData();
	std::vector<unsigned int> textureIndices = mesh->getUVIndexData();
	//create geometry object, and pass vertex and index data to it
	Geometry* geometry = new Geometry();
	if (mesh->shouldUnroll()) {
		std::vector<float> unrolledVertexData;
		for (unsigned int i : indices) {
			unsigned int index = i * 3;
			unrolledVertexData.push_back(vertexData.at(index));
			unrolledVertexData.push_back(vertexData.at(index + 1));
			unrolledVertexData.push_back(vertexData.at(index + 2));
		}
		geometry->addComponent(vertex, unrolledVertexData);
		//TODO: generate normals
		//the vertices are unrolled at this point, and we can assum that every 3 points will be 1 face...
		//need to take the cross product...
		if (!normalIndices.empty()) {
			std::vector<float> normals = mesh->getNormalData();
			std::vector<float> newNormals;

			for (unsigned int i : normalIndices) {
				unsigned int index = i * 3;
				newNormals.push_back(normals.at(index));
				newNormals.push_back(normals.at(index + 1));
				newNormals.push_back(normals.at(index + 2));
			}
			
			geometry->addComponent(normal, newNormals);
		} else {
			std::vector<float> normals;
			for (int i = 0; i < unrolledVertexData.size(); i += 9) {
				glm::vec3 point0 = glm::vec3(unrolledVertexData.at(i), unrolledVertexData.at(i + 1), unrolledVertexData.at(i + 2));
				glm::vec3 point1 = glm::vec3(unrolledVertexData.at(i + 3), unrolledVertexData.at(i + 4), unrolledVertexData.at(i + 5));
				glm::vec3 point2 = glm::vec3(unrolledVertexData.at(i + 6), unrolledVertexData.at(i + 7), unrolledVertexData.at(i + 8));

				glm::vec3 a = point1 - point0;
				glm::vec3 b = point2 - point0;

				glm::vec3 normal = glm::cross(a, b);
				normal = glm::normalize(normal);
				
				normals.push_back(normal.x);
				normals.push_back(normal.y);
				normals.push_back(normal.z);
				
				normals.push_back(normal.x);
				normals.push_back(normal.y);
				normals.push_back(normal.z);

				normals.push_back(normal.x);
				normals.push_back(normal.y);
				normals.push_back(normal.z);
			}

			geometry->addComponent(normal, normals);
		}
		if (!textureIndices.empty()) {
			std::vector<float> uvData = mesh->getUVData();
			std::vector<float> newUVData;
			for (unsigned int i : textureIndices) {
				unsigned int index = i * 2;
				newUVData.push_back(uvData.at(index));
				newUVData.push_back(uvData.at(index + 1));
			}
			geometry->addComponent(UV, newUVData);
		}

		//create render command and add geometry
		RenderCommand* rc = new RenderCommand(id,sLighted);
		rc->setGeometry(geometry);
		return rc;

	} else {
		geometry->addComponent(vertex, vertexData);
		if (!indices.empty())
			geometry->addEBO(indices);


		//create render command and add geometry
		RenderCommand* rc = new RenderCommand(id);
		rc->setGeometry(geometry);
		return rc;
	}

}

void RenderingEngine::cleanup() {
	m_shouldClose = true;
	return;
}