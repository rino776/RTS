#pragma once
namespace rendering{
class RenderCommand
{
public:

    void execute();

    void setID(unsigned int id) { m_id = id; }
    unsigned int id() { return m_id; }


private:
    unsigned int m_id;
};
}
