#pragma once
#include "AIMovementComponent.h"
#include "AttackComponent.h"
#include "FireBall.h"

namespace XYZRoguelike {
class AIDeceasedMagician : public XYZEngine::AIMovementComponent {
   public:
    AIDeceasedMagician(XYZEngine::GameObject* gameObject);
    void Update(float deltaTime) override;

   private:
    float AttackSpeed = 2.f;
    float teleportRollback = 0.0f;
    float dangerousDistance = 110.0f;
    XYZEngine::TransformComponent* objectTransform;
    XYZEngine::GameObject* selfObject;
    FireBall* fireballUp;
    FireBall* fireballDown;
    FireBall* fireballRight;
    FireBall* fireballLeft;
};
}  // namespace XYZRoguelike