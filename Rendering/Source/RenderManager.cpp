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
		m_shaderManager->bindAttribute(rc.material(), "View", m_Camera->getViewMatrix());
		m_shaderManager->bindAttribute(rc.material(), "Projection", m_Camera->getProjectionMatrix(false));
		m_shaderManager->bindAttribute(rc.material(), "lightPos", glm::vec3(3.0f,5.0f,5.0f));
		m_shaderManager->bindAttribute(rc.material(), "viewPos", -m_Camera->getTransform()->Position());
		rc.execute();
	}
}

void RenderManager::addRenderCommand(RenderCommand* rc)
{
	m_renderCommands.push_back(*rc);
}

RenderManager::~RenderManager() {
	
}