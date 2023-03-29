#include "Camera.h"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace rendering;

Camera::Camera() {
    m_cameraPos = glm::vec3(0);
    m_cameraDir = glm::normalize(m_cameraPos - m_cameraTarget);
    glm::vec3 worldup = glm::vec3(0.0f, 1.0f, 0.0f);
    m_cameraRight = glm::normalize(glm::cross(worldup, m_cameraDir));
    m_cameraUp = glm::cross(m_cameraDir, m_cameraRight);
}

glm::mat4 rendering::Camera::getProjectionMatrix(bool ortho)
{
    if (ortho) {

        float viewportRatio = (float)m_screenDetails->width / (float)m_screenDetails->height;
        float screenRatio = 800.0f / 600.0f;
        float VA = viewportRatio / screenRatio;
        float width = 800.0f;
        float height = 600.0f;

        if(viewportRatio >= screenRatio)
            return glm::ortho(-VA * width/2.0f, VA * width/2.0f, -height/2.0f, height/2.0f, -1.0f, 1.0f);

        return glm::ortho(-width/2.0f, width / 2.0f, -VA * height/2.0f, VA * height / 2.0f, -1.0f, 1.0f);
    }

    return glm::mat4();
}
