#pragma once

#include <WindowManager.h>
#include <RenderManager.h>
#include <InputManager.h>
#include <thread>
#include <memory>
#include <Entity.h>
#include <RenderCommand.h>
#include <Sprite.h>
#include <Mesh.h>
#include <mutex>
#include <CameraController.h>


namespace rendering {
class RenderingEngine
{
public:
	RenderingEngine(std::shared_ptr<core::InputManager>);
	void init();
	std::thread start();
	bool shouldClose() { return m_shouldClose; };
	void setDirtyEntities(std::vector<core::Entity*>& dirtyEnts);
	void setCameraTransform(core::Transform* transform);
	core::Transform* getCameraTransform();
	void setShouldClose(bool bShouldClose) { m_shouldClose = bShouldClose; };

protected:
	RenderCommand* createSprite(core::Sprite* sprite, unsigned int id);
	RenderCommand* createMesh(core::Mesh* mesh, unsigned int id);
	void renderLoop();
	void cleanup();

private:
	std::unique_ptr<WindowManager> m_windowManager;
	std::unique_ptr<RenderManager> m_renderManager;
	bool m_shouldClose = false;
	//move this to RenderManager?
	void updateEntities();
	std::vector<core::Entity*> m_dirtyEnts;
	std::shared_ptr<core::InputManager> m_inputManager;




};
}

