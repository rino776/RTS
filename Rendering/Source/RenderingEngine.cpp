#include "RenderingEngine.h"
#include <RenderingEngine.h>
#include <glm/ext/matrix_transform.hpp>
#include <Transform.h>
using namespace rendering;
using namespace core;

void RenderingEngine::init() {
	printf("Started Rendering Thread\n");
	m_windowManager = std::make_unique<WindowManager>();
	m_shouldClose = !m_windowManager->createWindow(800,600,"Hello World!");
	m_renderManager = std::make_unique<RenderManager>();
	renderLoop();
}

std::thread RenderingEngine::start() {
	
	return std::thread(&RenderingEngine::init, this);
}

void RenderingEngine::renderLoop() {
	
	while (!m_windowManager->shouldClose()) {
		//update stuff here
		m_windowManager->updateWindow();

		if (m_windowManager->dirty()) {
			m_renderManager->getCamera()->setScreenDetails(m_windowManager->getDetails());
			m_windowManager->setDirty(false);
		}
		
		//TODO: move these into the render pass?
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		updateEntities();
		m_renderManager->renderPass();
	}
	cleanup();
}

void RenderingEngine::updateEntities() {
	for (Entity* e : m_dirtyEnts) {
		//we probably want to check id here as well, to see if it is a new RC or an updated one...
		//or should we always create new ones, and delete the old ones?
		RenderCommand* rc{};
		Component* renderable;
		renderable = e->getComponent(eMesh);
		if (renderable) {
			//createMeshRC
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
	
		if(rc)
			m_renderManager->addRenderCommand(rc);
	}

	m_dirtyEnts.clear();
}

void RenderingEngine::setDirtyEntities(std::vector<Entity*>& dirtyEnts) {
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

void RenderingEngine::cleanup() {
	m_shouldClose = true;
	return;
}