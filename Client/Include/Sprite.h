#pragma once
#include "Component.h"
namespace core{
class Sprite :
    public Component
{
public:
    Sprite();
    void setWidth(float width) { m_width = width; }
    void setHeight(float height) { m_height = height; }
    void setTexId(int texID) { m_texID = texID; };

    float width() { return m_width; }
    float height() { return m_height; }
    int texID() { return m_texID; }

private:
    float m_width;
    float m_height;
    int m_texID;
    //colour?
};

}

