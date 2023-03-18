#include "RenderManager.h"
#include <iostream>
#include <GLFW/glfw3.h>

using namespace rendering;

RenderManager::RenderManager() {
	m_shaderManager = std::make_unique<ShaderManager>();
	m_renderCommands = std::vector<RenderCommand>();
	m_Camera = std::make_unique<Camera>();
}

void RenderManager::renderPass()
{
	for (RenderCommand& rc : m_renderCommands) {
		m_shaderManager->useShader(rc.material());
		m_shaderManager->bindAttribute(rc.material(), "Model", rc.modelMatrix());
		m_shaderManager->bindAttribute(rc.material(), "Projection", m_Camera->getProjectionMatrix(true));
		rc.execute();
	}
}

void RenderManager::addRenderCommand(RenderCommand* rc)
{
	m_renderCommands.push_back(*rc);
}

RenderManager::~RenderManager() {
	
}