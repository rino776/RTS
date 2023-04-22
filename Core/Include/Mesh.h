#pragma once
#include "Component.h"
#include <Point.h>
#include <Point2D.h>
#include <vector>
namespace core{
class Mesh :
    public Component
{
public:
    Mesh();
    Mesh(std::vector<Point> vertices, std::vector<Point> normals, std::vector<Point2D> uv, std::vector<unsigned int> indices, std::vector<unsigned int> normalIndices, std::vector<unsigned int> textureIndices);
    //TODO: load in from file (obj file?)
    std::vector<float> getVertexData();
    std::vector<float> getNormalData();
    std::vector<float> getUVData();
    std::vector<unsigned int> getIndexData(){ return m_indices; }
    std::vector<unsigned int> getNormalIndexData() { return m_normalIndices; }
    std::vector<unsigned int> getUVIndexData() { return m_textureIndices; }
private:
    //TODO: change to wrapper of point array?
    std::vector<Point> m_vertices;
    std::vector<Point> m_normals;
    std::vector<Point2D> m_textureCoords;
    std::vector<unsigned int> m_indices;
    std::vector<unsigned int> m_normalIndices;
    std::vector<unsigned int> m_textureIndices;
    bool m_indexed;
};

}

