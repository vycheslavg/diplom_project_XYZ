#pragma once
#include "AIMovementComponent.h"
#include "AttackComponent.h"
#include "Weapon.h"

#include <cassert>
namespace XYZRoguelike {
class AISwordMan : public XYZEngine::AIMovementComponent {
   public:
    AISwordMan(XYZEngine::GameObject* gameObject);
    void Update(float deltaTime) override;

   private:
    AttackComponent* attackComponent = nullptr;
    float meleeAttackRadius = 70.f;
    float preAttackDelay = 1.5f;
    float offsetSword = 40.f;
};

}  // namespace XYZRoguelike