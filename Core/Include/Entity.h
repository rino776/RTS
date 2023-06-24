#pragma once
#include <unordered_map>
#include <Component.h>
#include <memory>
#include <InputManager.h>

namespace core {
class Entity
{
public:
    Entity();
    virtual void update();
    bool addComponent(Component* component);
    Component* getComponent(ComponentType type);

    int id() { return m_id; }
    void setID(int id) { m_id = id; }

    bool isDirty() { return m_isDirty; }
    void setDirty(bool isDirty) { m_isDirty = isDirty; }
    void setInputManager(std::shared_ptr<InputManager> inputManager) { 
        m_inputManager = inputManager;
    }

protected:
    std::shared_ptr<InputManager> m_inputManager;
private:
    int m_id;
    //whether this entity needs to be re-rendered or not
    bool m_isDirty;
    std::unordered_map<ComponentType, Component*> m_components;

};
}

