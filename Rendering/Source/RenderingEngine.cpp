#include "RenderingEngine.h"

using namespace rendering;
using namespace core;

void RenderingEngine::init() {
	m_windowManager = std::make_unique<WindowManager>(WindowManager());
	m_shouldClose = !m_windowManager->createWindow(800,600,"Hello World!");
	m_shaderManager = std::make_unique<ShaderManager>(ShaderManager());

	renderLoop();
}

std::thread RenderingEngine::start() {
	
	return std::thread(&RenderingEngine::init, this);
}

void RenderingEngine::renderLoop() {
	
	while (!m_windowManager->shouldClose()) {
		//update stuff here
		m_windowManager->updateWindow();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		updateEntities();
		for (RenderCommand* rc : m_renderCommands) {
			m_shaderManager->useShader(rc->material());
			rc->execute();
		}
	}
	cleanup();
}

void RenderingEngine::updateEntities() {
	for (Entity* e : m_dirtyEnts) {
		//we probably want to check id here as well, to see if it is a new RC or an updated one...
		//or should we always create new ones, and delete the old ones?
		
		Component* renderable;
		renderable = e->getComponent(eMesh);
		if (renderable) {
			//createMeshRC
			continue;
		}
		renderable = e->getComponent(eSprite);
		if (renderable) {
			RenderCommand* rc = createSprite((Sprite*)renderable, e->id());
			m_renderCommands.push_back(rc);
			continue;
		}
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