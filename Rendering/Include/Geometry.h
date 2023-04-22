#pragma once
#include <vector>
#include <glm/ext/vector_float3.hpp>
namespace rendering {

    typedef enum AttributePointerType {
        vertex = 0,
        colour,
        normal,
        UV,
        index,
        
    } AttributePointerType;


class Geometry
{
public:
    Geometry();

    void addComponent(AttributePointerType type, std::vector<float>& data);
    void addEBO(std::vector<unsigned int>& data);
    unsigned int id() { return m_id; }
    int vertexCount() { return m_vertexCount; }
    int indexCount() { return m_indexCount; }
    bool isIndexed() { return m_isIndexed; }
private:
    int getStride(AttributePointerType type);
    //the VAO id
    unsigned int m_id;
    int m_vertexCount;
    int m_indexCount;
    unsigned int m_EBO;
    bool m_isIndexed;

};
}
