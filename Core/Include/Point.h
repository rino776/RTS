#pragma once
#include <glm/ext/vector_float3.hpp>
namespace core{
class Point
{
public:
    Point(double x, double y, double z);
    glm::vec3 toGLMVector();

    double x() { return m_x; }
    double y() { return m_y; }
    double z() { return m_z; }

private:
    double m_x;
    double m_y;
    double m_z;
};

}

