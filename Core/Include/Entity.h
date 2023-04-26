#pragma once
#include <unordered_map>
#include <Component.h>

namespace core {
class Entity
{
public:
    Entity();
    void update();
    bool addComponent(Component* componant);
    Component* getComponent(ComponentType type);

    int id() { return m_id; }
    void setID(int id) { m_id = id; }

    bool isDirty() { return m_isDirty; }
    void setDirty(bool isDirty) { m_isDirty = isDirty; }

private:
    int m_id;
    //whether this entity needs to be re-rendered or not
    bool m_isDirty;
    std::unordered_map<ComponentType, Component*> m_components;
};
}

