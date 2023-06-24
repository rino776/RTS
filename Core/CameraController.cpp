#include "CameraController.h"
#include "Transform.h"

using namespace core;
CameraController::CameraController()
{
    addComponent(new Transform(glm::vec3(0.0,0.0,6.0)));
}


void CameraController::update() {
    Transform* transform = (Transform*)getComponent(eTransform);
    glm::vec3 currentPos = transform->Position();

    double speed = 0.1;
    if(m_inputManager){
        
        if (m_inputManager->getKeyDown(key_w)) {
            currentPos.z -= speed; //TODO: delta time
            
        }
        
        if (m_inputManager->getKeyDown(key_s)) {
            currentPos.z += speed; //TODO: delta time
        }
        
        if (m_inputManager->getKeyDown(key_a)) {
            currentPos.x -= speed; //TODO: delta time
            
        }
        
        if (m_inputManager->getKeyDown(key_d)) {
            currentPos.x += speed; //TODO: delta time
        }

        if (m_inputManager->getKeyDown(key_q)) {
            currentPos.y += speed; //TODO: delta time

        }

        if (m_inputManager->getKeyDown(key_e)) {
            currentPos.y -= speed; //TODO: delta time
        }

        transform->setPosition(currentPos);
    }
}