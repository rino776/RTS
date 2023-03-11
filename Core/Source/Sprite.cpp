#include "Sprite.h"

using namespace core;

Sprite::Sprite() {
    //TODO change these back to 0's
    //they are at 100 only until we create something for setting them up properly
    m_type = eSprite;
    m_width = 100.0f;
    m_height = 100.0f;
    m_texID = 0;
}