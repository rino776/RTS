#include "RenderingEngine.h"


using namespace rendering;

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
	}
	cleanup();
}

void RenderingEngine::cleanup() {
	m_shouldClose = true;
	return;
}