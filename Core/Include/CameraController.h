#pragma once
#include "Entity.h"

namespace core{
class CameraController : 
    public Entity
{
public:
    CameraController();
    void update() override;
};


}

