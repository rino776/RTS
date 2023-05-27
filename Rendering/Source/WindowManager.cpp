#include "WindowManager.h"

using namespace rendering;
using namespace core;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	//need some way to trigger an update to the member variables :/
	//maybe like a static 'is dirty' flag, that when true force update?
	//think about this more later...
	glViewport(0, 0, width, height);

	WindowManager* manager = (WindowManager*)(glfwGetWindowUserPointer(window));
	if (manager) {
		manager->setDetails(width, height);
		manager->setDirty(true);
	}
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	WindowManager* manager = (WindowManager*)(glfwGetWindowUserPointer(window));

	if (manager && action != GLFW_REPEAT) {
		manager->getInputManager()->setKey(key, action);
	}
}

WindowManager::WindowManager(InputManagerPtr inputManager) {
	m_inputManager = inputManager;
}

bool WindowManager::createWindow(int width, int height, const char* title) {
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_details.height = height;
	m_details.width = width;

	m_window = glfwCreateWindow(m_details.width, m_details.height, title, NULL, NULL);
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

	m_dirty = true;

	glViewport(0, 0, m_details.width, m_details.height);

	glfwSetWindowUserPointer(m_window, (void*)this);

	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	glfwSetKeyCallback(m_window, key_callback);
	
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