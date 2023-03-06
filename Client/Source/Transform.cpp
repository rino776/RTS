#include "Transform.h"
using namespace core;
using namespace glm;


//TODO: make the origin a const?
Transform::Transform() {
    m_type = eTransform;
    m_position = vec3(0, 0, 0);
    m_rotation = vec3(0, 0, 0);
    m_scale = vec3(0, 0, 0);
}


mat4 Transform::getTransformMatrix() {
    
    mat4 transform = mat4(1.0);
    transform = translate(transform, m_position);
    transform = rotate(transform, m_rotation.x, vec3(1, 0, 0));
    transform = rotate(transform, m_rotation.y, vec3(0, 1, 0));
    transform = rotate(transform, m_rotation.z, vec3(0, 0, 1));
    transform = scale(transform, m_scale);
    
    return transform;
}