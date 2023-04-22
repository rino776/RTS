#pragma once
#include <glm/ext/vector_float2.hpp>
namespace core{
class Point2D
{
public:
    Point2D(double x, double y);
    glm::vec2 toGLMVector();

    double x() { return m_x; }
    double y() { return m_y; }

private:
    double m_x;
    double m_y;

};
}

