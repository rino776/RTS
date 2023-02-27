#pragma once
#include <WindowManager.h>
#include <thread>

namespace rendering{
	//forward declarations

class RenderingEngine
{
public:
	void init();
	std::thread start();
	void cleanup();
	void renderLoop();

	bool shouldClose() { return m_shouldClose; };

protected:

private:

	WindowManagerPtr m_windowManager;
	bool m_shouldClose = false;
};
}

