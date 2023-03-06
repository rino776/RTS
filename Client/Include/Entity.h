#pragma once
#include <unordered_map>
#include <Component.h>

namespace core {
class Entity
{
public:

    void update();
    bool addComponent(Component* componant);

private:
    int m_id;
    //whether this entity needs to be re-rendered or not
    bool m_isDirty;
    std::unordered_map<int, Component*> m_components;
};
}

