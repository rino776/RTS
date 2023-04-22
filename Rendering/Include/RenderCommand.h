#pragma once
#include <ShaderManager.h>
#include <Geometry.h>

namespace rendering {

class RenderCommand
{
public:
    RenderCommand(unsigned int id, ShaderType material = sBasic);

    void execute();

    unsigned int id() { return m_id; }
    ShaderType material() { return m_material; }
    
    //should only have 1 set of geometry per render command.
    void setGeometry(Geometry* geometry) { m_geometry = geometry; }
    void setModelMatrix(glm::mat4 modelMatrix) { m_modelMatrix = modelMatrix; }
    glm::mat4 modelMatrix() { return m_modelMatrix; }

private:
    unsigned int m_id;
    ShaderType m_material;
    Geometry* m_geometry;
    glm::mat4 m_modelMatrix;
};
}
