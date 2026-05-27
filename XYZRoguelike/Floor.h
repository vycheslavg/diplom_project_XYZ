#pragma once

#include "GameObject.h"

#include <GameWorld.h>
#include <ResourceSystem.h>
#include <SpriteRendererComponent.h>

namespace XYZRoguelike {
class Floor {
   public:
    Floor(const XYZEngine::Vector2Df position, int textureMapIndex);
    XYZEngine::TransformComponent* transform;

   private:
    XYZEngine::GameObject* gameObject;
};
}  // namespace XYZRoguelike
