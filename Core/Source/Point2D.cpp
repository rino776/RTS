#include "Point2D.h"
using namespace core;

Point2D::Point2D(double x, double y) {
    m_x = x;
    m_y = y;
}

glm::vec2 Point2D::toGLMVector() {
    return glm::vec2((float)m_x, (float)m_y);
}