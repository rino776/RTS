#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace core {

class Transform : 
    public Component
{
public:
    Transform(glm::vec3 position);
    Transform();
    glm::vec3 Position() { return m_position;};
    glm::vec3 Rotation() { return m_rotation;};
    glm::vec3 Scale() { return m_scale;}

    void setPosition(glm::vec3 position) { m_position = position; };
    void setRotation(glm::vec3 rotation) { m_rotation = rotation; };
    void setScale(glm::vec3 scale) { m_scale = scale; };

    glm::mat4 getTransformMatrix();

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

};
}

