#include "Camera.h"
#include <glm/geometric.hpp>

using namespace rendering;

Camera::Camera(bool ortho) {
    m_ortho = ortho;
    m_cameraPos = glm::vec3(0);
    m_cameraDir = glm::normalize(m_cameraPos - m_cameraTarget);
    glm::vec3 worldup = glm::vec3(0.0f, 1.0f, 0.0f);
    m_cameraRight = glm::normalize(glm::cross(worldup, m_cameraDir));
    m_cameraUp = glm::cross(m_cameraDir, m_cameraRight);
}
