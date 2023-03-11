#pragma once
#include <ShaderManager.h>
namespace rendering{
class RenderCommand
{
public:
    RenderCommand(unsigned int id);

    void execute();

    void setID(unsigned int id) { m_id = id; }
    unsigned int id() { return m_id; }
    ShaderType material() { return m_material; }

private:
    unsigned int m_id;
    ShaderType m_material;
    unsigned int m_VAO;

};
}
