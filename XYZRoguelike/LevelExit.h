#pragma once

#include <GameObject.h>
#include <SpriteRendererComponent.h>
#include <SpriteColliderComponent.h>
namespace XYZRoguelike 
{
class LevelExit {
   public:
    LevelExit(const XYZEngine::Vector2Df position);
    void Transition(XYZEngine::Collision collision);
    XYZEngine::GameObject* GetGameObject();
    void SetIsDoorClosed(bool isClosed);
   private:
    XYZEngine::GameObject* gameObject;
    bool isDoorClosed = false;
};
}  // namespace XYZRoguelike