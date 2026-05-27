#pragma once
#include "GameObject.h"

#include <GameWorld.h>
#include <ResourceSystem.h>

class Wall {
   public:
    Wall(const XYZEngine::Vector2Df position, int indexTexture);
    XYZEngine::TransformComponent* transform;
   private:
    XYZEngine::GameObject* gameObject;
};
