#include "Camera.h"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace rendering;
using namespace core;
Camera::Camera() {
    m_cameraTransform = new Transform(glm::vec3(0.0,0.0,6.0));
    m_screenDetails = nullptr;
}

glm::mat4 Camera::getProjectionMatrix(bool ortho)
{
    float width = 800.0f;
    float height = 600.0f;
    float screenRatio = 800.0f / 600.0f;
    float viewportRatio = (float)m_screenDetails->width / (float)m_screenDetails->height;
    float VA = viewportRatio / screenRatio;


    if (ortho) {
        if(viewportRatio >= screenRatio)
            return glm::ortho(-VA * width/2.0f, VA * width/2.0f, -height/2.0f, height/2.0f, -1.0f, 1.0f);

        return glm::ortho(-width/2.0f, width / 2.0f, -VA * height/2.0f, VA * height / 2.0f, -1.0f, 1.0f);
    }

    return glm::perspective(glm::radians(45.0f), viewportRatio, 0.1f, 100.0f);

}

glm::mat4 Camera::getViewMatrix() {
    glm::mat4 view = glm::mat4(1.0);

    view = glm::translate(view, -m_cameraTransform->Position());
    
    //view = glm::rotate(view, glm::radians(25.0f), glm::vec3(1, 0, 0));
    //view = glm::rotate(view, glm::radians(-25.0f), glm::vec3(0, 1, 0));

    return view;
}