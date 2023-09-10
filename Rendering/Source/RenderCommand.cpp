#include "RenderCommand.h"
#include <glad/glad.h>

using namespace rendering;



RenderCommand::RenderCommand(unsigned int id, ShaderType material) :
        m_modelMatrix(1.0)
    ,   m_id(id)
    ,   m_material(material)
    ,   m_geometry(nullptr)
{
}

void RenderCommand::execute() {
    
    glBindVertexArray(m_geometry->id());
    //TODO: setting uniforms, attributes etc
    if (m_geometry->isIndexed()) {
        glDrawElements(GL_TRIANGLES, m_geometry->indexCount(), GL_UNSIGNED_INT, 0);
    }else{
        glDrawArrays(GL_TRIANGLES, 0, m_geometry->vertexCount());
    }
}