#include "Mesh.h"
using namespace core;

Mesh::Mesh() {
    m_type = eMesh;
    //basic square at the moment
    m_vertices.push_back(Point(-0.5,  -0.5,0.0));
    m_vertices.push_back(Point( 0.5,  -0.5,0.0));
    m_vertices.push_back(Point( 0.5,   0.5,0.0));
    m_vertices.push_back(Point(-0.5,   0.5,0.0));

    m_indices.push_back(0);
    m_indices.push_back(1);
    m_indices.push_back(2);

    m_indices.push_back(0);
    m_indices.push_back(2);
    m_indices.push_back(3);

    m_indexed = true;
    m_isTriangulated = false;

}

std::vector<float> Mesh::getVertexData()
{
    std::vector<float> vertexData;
    
    for (Point& p : m_vertices) {
        vertexData.push_back((float)p.x());
        vertexData.push_back((float)p.y());
        vertexData.push_back((float)p.z());
    }

    return vertexData;
}

std::vector<int> Mesh::getIndexData()
{
    return m_indices;
}


