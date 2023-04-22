#pragma once
#include <Mesh.h>
namespace loader{
class ObjLoader
{
public:
    static core::Mesh* loadFromFile(const char* path);

};
}

