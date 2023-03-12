#pragma once
#include <vector>
#include <glm/ext/vector_float3.hpp>
namespace rendering {

    typedef enum AttributePointerType {
        vertex = 0,
        colour,
        UV
    } AttributePointerType;


class Geometry
{
public:
    Geometry();

    void addComponent(AttributePointerType type, std::vector<float>& data);

    unsigned int id() { return m_id; }
    int vertexCount() { return m_vertexCount; }

private:
    int getStride(AttributePointerType type);
    //the VAO id
    unsigned int m_id;
    int m_vertexCount;

};
}
