#include "RenderCommand.h"
#include <glad/glad.h>

using namespace rendering;



RenderCommand::RenderCommand(unsigned int id) {
    m_id = id;
    m_material = sBasic;    
}

void RenderCommand::execute() {
    
    //TODO: setting uniforms, attributes etc

    glBindVertexArray(m_geometry->id());
    glDrawArrays(GL_TRIANGLES, 0, m_geometry->vertexCount());
}