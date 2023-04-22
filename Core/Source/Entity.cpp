#include "Entity.h"

using namespace core;

Entity::Entity() {
    //force it 
    m_isDirty = true;
    //id of -1 means it is invalid.
    //TODO: think of good way to set the ID.
    m_id = -1;
}


void Entity::update() {
    for (auto c : m_components) {
        c.second->update();
    }
}

bool Entity::addComponent(Component* component) {
    if (!component)
        return false;
    auto c = m_components.emplace(component->getType(), component);
    return c.second;
}

Component* core::Entity::getComponent(ComponentType type)
{
    auto component = m_components.find(type);

    if (component != m_components.end())
        return component->second;

    return nullptr;
}
