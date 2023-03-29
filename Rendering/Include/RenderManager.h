#pragma once
#include <RenderCommand.h>
#include <Camera.h>
#include <memory>

namespace rendering{

class RenderManager
{
public:
	RenderManager();
	virtual ~RenderManager();
	void renderPass();
	void addRenderCommand(RenderCommand* rc);
	std::unique_ptr<Camera>& getCamera() { return m_Camera; }

private:
	std::vector<RenderCommand> m_renderCommands;
	std::unique_ptr<ShaderManager> m_shaderManager;
	std::unique_ptr<Camera> m_Camera;

};
}
