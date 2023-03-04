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