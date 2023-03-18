#include "RenderManager.h"
#include <iostream>
#include <GLFW/glfw3.h>

using namespace rendering;

RenderManager::RenderManager() {
	m_shaderManager = std::make_unique<ShaderManager>(ShaderManager());
	m_renderCommands = std::vector<RenderCommand>();
}

void RenderManager::renderPass()
{
	for (RenderCommand& rc : m_renderCommands) {
		m_shaderManager->useShader(rc.material());
		rc.execute();
	}
}

void RenderManager::addRenderCommand(RenderCommand* rc)
{
	m_renderCommands.push_back(*rc);
}

RenderManager::~RenderManager() {
	
}