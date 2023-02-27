#include "RenderingEngine.h"

using namespace rendering;

void RenderingEngine::init() {
	//m_windowManager = std::make_shared<WindowManager>(new WindowManager());
	
	//m_windowManager->createWindow(800,600,"Hello World!");
}

std::thread RenderingEngine::start() {
	
	return std::thread(&RenderingEngine::renderLoop, this);
}

void RenderingEngine::renderLoop() {
	
	printf("Hello from a thread!\n");
	printf("going to sleep\n");
	std::this_thread::sleep_for(std::chrono::seconds(2));
	printf("I am now awake!\n");
	m_shouldClose = true;
	
}

void RenderingEngine::cleanup() {
	return;
}