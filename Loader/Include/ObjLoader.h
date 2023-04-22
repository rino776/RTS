#pragma once
#include <Mesh.h>
#include <string>
namespace loader{
class ObjLoader
{
public:
    static core::Mesh* loadFromFile(const char* path);

private:
    typedef struct Face {
        unsigned int vertexIndex;
        unsigned int uvIndex;
        unsigned int normalIndex;
    } Face;

    static Face* parseFaceIndex(const std::string& face);
};
}

