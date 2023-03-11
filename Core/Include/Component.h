#pragma once
namespace core {

    typedef enum Type {
        eMesh = 0, //3D
        eSprite, //2D
        eTransform, //position, scale, rotation etc
    } ComponentType;

class Component
{
public:

    virtual void update();
    ComponentType getType() { return m_type; };
protected:
    ComponentType m_type;

};
}

