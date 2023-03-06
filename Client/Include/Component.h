#pragma once
namespace core {

    enum Type {
        eMesh, //3D
        eSprite, //2D
        eTransform, //position, scale, rotation etc
    };

class Component
{
public:

    virtual void update();
    int getType() { return m_type; };
protected:
    int m_type;

};
}

