#pragma once
#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <WindowManager.h>
#include <Transform.h>

namespace rendering {

class Camera
{
public:
    Camera();
    glm::mat4 getProjectionMatrix(bool ortho);
    glm::mat4 getViewMatrix();
    core::Transform* getTransform() { return m_cameraTransform; }

    void setScreenDetails(ScreenDetails* details) { m_screenDetails = details; }
    
    
    void setPos(core::Transform* transform) { m_cameraTransform = transform; }
    
private:
    core::Transform* m_cameraTransform;

    ScreenDetails* m_screenDetails;

};
}
