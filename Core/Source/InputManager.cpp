#include "InputManager.h"
#include <mutex>
using namespace core;
std::mutex g_inputMutex;

InputManager::InputManager()
{
    m_keyState = new bool[key_max_value];
    memset(m_keyState, false, key_max_value);
}

InputManager::~InputManager() {

}

bool InputManager::getKeyDown(Key key) {
    std::lock_guard<std::mutex> lock(g_inputMutex);
    return m_keyState[key];
}

void InputManager::setKey(int key, int action)
{
     std::lock_guard<std::mutex> lock(g_inputMutex);
    m_keyState[key] = action;
}


