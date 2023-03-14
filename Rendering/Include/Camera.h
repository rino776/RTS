#pragma once
#include <glm/vec3.hpp>

namespace rendering {
class Camera
{
public:
    Camera(bool ortho);

private:
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraDir;
    glm::vec3 m_cameraTarget;
    glm::vec3 m_cameraRight;
    glm::vec3 m_cameraUp;

    bool m_ortho;
};
}
