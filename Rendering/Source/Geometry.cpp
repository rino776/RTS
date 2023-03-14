#include "Geometry.h"
#include <glad/glad.h>

using namespace rendering;

Geometry::Geometry()
{
    m_vertexCount = 0;
    glGenVertexArrays(1, &m_id);
}

void Geometry::addComponent(AttributePointerType type, std::vector<float>& data) {

    //make sure we know how many vertices there are
    if (type == vertex)
        m_vertexCount = data.size();
    
    glBindVertexArray(m_id);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

    int stride = getStride(type);
    glVertexAttribPointer(0, stride, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(type);
}

int Geometry::getStride(AttributePointerType type) {
    switch (type) {
    case vertex:
        return 3;
    case colour:
        return 3;
    case UV:
        return 2;
    default:
        return 3;
    }
}