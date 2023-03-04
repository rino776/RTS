#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace rendering {

class WindowManager
{
public:

	virtual ~WindowManager();
	bool createWindow(int width, int height, const char* title);
	void updateWindow();

	bool shouldClose();
	GLFWwindow* window() { return m_window;};

	
private:

	GLFWwindow* m_window;
	int m_width;
	int m_height;
};

}

