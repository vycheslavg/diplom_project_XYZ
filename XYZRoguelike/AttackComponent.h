#pragma once
#include "TransformComponent.h"
#include "Weapon.h"
namespace XYZRoguelike {
class AttackComponent : public XYZEngine::Component {
   public:
    AttackComponent(XYZEngine::GameObject* gameObject);
    void Attack();

   private:
    void Update(float deltaTime) override;
    void Render() override;
    Weapon* weapon;
    float delayAttack = 0.f;
    float attackSpeed = 0.f;
};

}  // namespace XYZRoguelike