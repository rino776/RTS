#include "WindowManager.h"

using namespace rendering;

bool WindowManager::createWindow(int width, int height, const char* title) {
	if (glfwInit())
		return false;

	m_height = height;
	m_width = width;

	m_window = glfwCreateWindow(m_width, m_height, title, NULL, NULL);


	if (!m_window) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);
	return true;
}

bool WindowManager::shouldClose() {
	return glfwWindowShouldClose(m_window);
}

WindowManager::~WindowManager() {
	glfwTerminate();
}