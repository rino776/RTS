#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <InputManager.h>

namespace core {
	typedef std::shared_ptr<InputManager> InputManagerPtr;
}

namespace rendering {

	typedef struct {
		int width;
		int height;
	} ScreenDetails;
	
class WindowManager
{
public:
	WindowManager(core::InputManagerPtr inputManager);
	virtual ~WindowManager();
	bool createWindow(int width, int height, const char* title);
	void updateWindow();

	bool shouldClose();
	GLFWwindow* window() { return m_window;};

	void setDetails(int width, int height) { m_details.width = width; m_details.height = height; }
	ScreenDetails* getDetails() { return &m_details; }
	void setDirty(bool dirty) { m_dirty = dirty; }
	const bool dirty() { return m_dirty; }

	core::InputManagerPtr getInputManager() { return m_inputManager; }

private:
	bool m_dirty;
	GLFWwindow* m_window;
	ScreenDetails m_details;
	core::InputManagerPtr m_inputManager;
};

}

