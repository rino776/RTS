#pragma once

#include <WindowManager.h>
#include <thread>
#include <memory>


namespace rendering {
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
	std::unique_ptr<WindowManager> m_windowManager;
	bool m_shouldClose = false;
};
}

