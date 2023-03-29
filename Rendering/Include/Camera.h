#pragma once
#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>>
#include <WindowManager.h>

namespace rendering {

class Camera
{
public:
    Camera();
    glm::mat4 getProjectionMatrix(bool ortho);

    void setScreenDetails(ScreenDetails* details) { m_screenDetails = details; }

private:
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraDir;
    glm::vec3 m_cameraTarget;
    glm::vec3 m_cameraRight;
    glm::vec3 m_cameraUp;

    ScreenDetails* m_screenDetails;

};
}
