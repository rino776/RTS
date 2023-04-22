#include "Mesh.h"
#include <iterator>
using namespace core;

Mesh::Mesh() {
    m_type = eMesh;
    //basic square at the moment
    m_vertices.push_back(Point(-0.5,  -0.5, -0.5));
    m_vertices.push_back(Point( 0.5,  -0.5, -0.5));
    m_vertices.push_back(Point( 0.5,   0.5, -0.5));
    m_vertices.push_back(Point(-0.5,   0.5, -0.5));

    m_vertices.push_back(Point(-0.5,  -0.5, 0.5));
    m_vertices.push_back(Point( 0.5,  -0.5, 0.5));
    m_vertices.push_back(Point( 0.5,   0.5, 0.5));
    m_vertices.push_back(Point(-0.5,   0.5, 0.5));

    // Initialize index array
    unsigned int indices[] = { 
        0, 1, 2, 0, 2, 3, 
        5, 4, 7, 5, 7, 6, 
        2, 6, 7, 3, 2, 7, 
        0, 1, 5, 0, 5, 4, 
        4, 0, 3, 4, 3, 7, 
        1, 5, 6, 1, 6, 2 
    };

    // Copy index array to vector
    m_indices.reserve(std::size(indices));
    std::copy(std::begin(indices), std::end(indices), std::back_inserter(m_indices));

    m_shouldUnroll = false;
}

Mesh::Mesh(std::vector<Point> vertices, std::vector<Point> normals, std::vector<Point2D> uv, std::vector<unsigned int> indices, std::vector<unsigned int> normalIndices, std::vector<unsigned int> textureIndices) {
    m_type = eMesh;

    m_vertices = vertices;
    m_normals = normals;
    m_textureCoords = uv;
    
    m_indices = indices;
    m_normalIndices = normalIndices;
    m_textureIndices = textureIndices;

    m_shouldUnroll = true;
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

std::vector<float> Mesh::getNormalData()
{
    std::vector<float> normalData;

    for (Point& p : m_normals) {
        normalData.push_back((float)p.x());
        normalData.push_back((float)p.y());
        normalData.push_back((float)p.z());
    }

    return normalData;
}


std::vector<float> Mesh::getUVData() {
    std::vector<float> uvData;

    for (Point2D& p : m_textureCoords) {
        uvData.push_back(p.x());
        uvData.push_back(p.y());
    }

    return uvData;

}


