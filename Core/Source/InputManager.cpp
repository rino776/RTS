#include "InputManager.h"
using namespace core;

InputManager::InputManager()
{
    m_keyState = new bool[key_max_value];
    memset(m_keyState, false, key_max_value);
}

InputManager::~InputManager() {

}

bool InputManager::getKeyDown(Key key) {
    return m_keyState[key];
}

void InputManager::setKey(int key, int action)
{
    m_keyState[key] = action;
}


