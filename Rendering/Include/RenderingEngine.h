#pragma once

#include <WindowManager.h>
#include <thread>
#include <memory>
#include<Entity.h>
#include <map>
#include <RenderCommand.h>
#include <Sprite.h>


namespace rendering {
class RenderingEngine
{
public:
	void init();
	std::thread start();
	void cleanup();
	void renderLoop();
	bool shouldClose() { return m_shouldClose; };
	void updateEntities(std::vector<core::Entity*>);

protected:
	RenderCommand* createSprite(core::Sprite* sprite);

private:
	std::unique_ptr<WindowManager> m_windowManager;
	bool m_shouldClose = false;
	//does this need to be lockable?
	std::vector<RenderCommand*> m_renderCommands;

};
}

