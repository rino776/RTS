#pragma once
#include <RenderCommand.h>
#include <memory>

namespace rendering{

class RenderManager
{
public:
	RenderManager();
	virtual ~RenderManager();
	void renderPass();
	void addRenderCommand(RenderCommand* rc);

private:
	std::vector<RenderCommand> m_renderCommands;
	std::unique_ptr<ShaderManager> m_shaderManager;
};
}
