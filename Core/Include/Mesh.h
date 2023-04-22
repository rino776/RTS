#pragma once
#include "Component.h"
#include <Point.h>
#include <vector>
namespace core{
class Mesh :
    public Component
{
public:
    Mesh();
    Mesh(std::vector<Point> vertices, std::vector<unsigned int> m_indices);
    //TODO: load in from file (obj file?)
    std::vector<float> getVertexData();
    std::vector<unsigned int> getIndexData();
private:
    //TODO: change to wrapper of point array?
    std::vector<Point> m_vertices;
    std::vector<unsigned int> m_indices;
    bool m_isTriangulated;
    bool m_indexed;
};

}

