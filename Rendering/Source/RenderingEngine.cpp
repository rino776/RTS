#include "RenderingEngine.h"

using namespace rendering;
using namespace core;

void RenderingEngine::init() {
	m_windowManager = std::make_unique<WindowManager>(WindowManager());
	
	m_shouldClose = !m_windowManager->createWindow(800,600,"Hello World!");

	renderLoop();
}

std::thread RenderingEngine::start() {
	
	return std::thread(&RenderingEngine::init, this);
}

void RenderingEngine::renderLoop() {
	
	while (!m_windowManager->shouldClose()) {
		//update stuff here
		m_windowManager->updateWindow();
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		for (RenderCommand* rc : m_renderCommands) {
			rc->execute();
		}

	}
	cleanup();
}
//do the incomming entitities need to be locked?
void RenderingEngine::updateEntities(std::vector<core::Entity*> entities) {
	for (Entity* e : entities) {
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
			m_renderCommands.push_back(createSprite((Sprite*)renderable));
			continue;
		}
	}
}

RenderCommand* RenderingEngine::createSprite(Sprite* sprite) {
	//create VAO
	//create Shader
}

void RenderingEngine::cleanup() {
	m_shouldClose = true;
	return;
}