#pragma once

#include <WindowManager.h>
#include <thread>
#include <memory>
#include<Entity.h>
#include <map>
#include <RenderCommand.h>
#include <Sprite.h>
#include <ShaderManager.h>


namespace rendering {
class RenderingEngine
{
public:
	void init();
	std::thread start();
	void cleanup();
	void renderLoop();
	bool shouldClose() { return m_shouldClose; };
	void setDirtyEntities(std::vector<core::Entity*>& dirtyEnts);

protected:
	RenderCommand* createSprite(core::Sprite* sprite);

private:
	std::unique_ptr<WindowManager> m_windowManager;
	std::unique_ptr<ShaderManager> m_shaderManager;
	bool m_shouldClose = false;
	//does this need to be lockable?
	std::vector<RenderCommand*> m_renderCommands;
	void updateEntities();
	std::vector<core::Entity*> m_dirtyEnts;



};
}

