#include "Point.h"
using namespace core;

Point::Point(double x, double y, double z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

glm::vec3 Point::toGLMVector() {
    return glm::vec3((float)m_x, (float)m_y, (float)m_z);
}