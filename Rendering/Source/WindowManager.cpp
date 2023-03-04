#include "WindowManager.h"

using namespace rendering;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	//need some way to trigger an update to the member variables :/
	//maybe like a static 'is dirty' flag, that when true force update?
	//think about this more later...
	glViewport(0, 0, width, height);
}

bool WindowManager::createWindow(int width, int height, const char* title) {
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_height = height;
	m_width = width;

	m_window = glfwCreateWindow(m_width, m_height, title, NULL, NULL);


	if (!m_window) {
		glfwTerminate();
		printf("Failed to create GLFW windo!");
		return false;
	}

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to init GLAD");
		return false;
	}

	glViewport(0, 0, m_width, m_height);

	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	return true;
}



void WindowManager::updateWindow() {
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

bool WindowManager::shouldClose() {
	return glfwWindowShouldClose(m_window);
}

WindowManager::~WindowManager() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}