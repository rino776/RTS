#include "Geometry.h"
#include <glad/glad.h>

using namespace rendering;

Geometry::Geometry() :
        m_EBO(0)
    ,   m_indexCount(-1)
    ,   m_vertexCount(-1)
    ,   m_isIndexed(false)
{
    m_isIndexed = false;
    glGenVertexArrays(1, &m_id);
}

void Geometry::addComponent(AttributePointerType type, std::vector<float>& data) {

    //make sure we know how many vertices there are
    if (type == vertex)
        m_vertexCount = data.size() / 3.0f;
    
    glBindVertexArray(m_id);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    int stride = getStride(type);
    glVertexAttribPointer(type, stride, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(type);
}


void Geometry::addEBO(std::vector<unsigned int>& data) {
    glBindVertexArray(m_id);

    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(int), data.data(), GL_STATIC_DRAW);
    m_isIndexed = true;
    m_indexCount = data.size();
}

int Geometry::getStride(AttributePointerType type) {
    switch (type) {
    case vertex:
        return 3;
    case colour:
        return 3;
    case UV:
        return 2;
    case normal:
        return 3;
    default:
        return 3;
    }
}