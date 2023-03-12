#pragma once
#include <ShaderManager.h>
#include <Geometry.h>

namespace rendering {

class RenderCommand
{
public:
    RenderCommand(unsigned int id);

    void execute();

    unsigned int id() { return m_id; }
    ShaderType material() { return m_material; }
    
    //should only have 1 set of geometry per render command.
    void setGeometry(Geometry* geometry) { m_geometry = geometry; }

private:
    unsigned int m_id;
    ShaderType m_material;
    Geometry* m_geometry;

};
}
