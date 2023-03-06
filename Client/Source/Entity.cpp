#include "Entity.h"


using namespace core;

void Entity::update() {
    for (auto c : m_components) {
        c.second->update();
    }
}

bool Entity::addComponent(Component* component) {

    auto c = m_components.emplace(component->getType(), component);
    return c.second;
}

Component* core::Entity::getComponent(ComponentType type)
{
    auto component =  m_components.find(type);

    if (component != m_components.end())
        return component->second;

    return nullptr;
}
