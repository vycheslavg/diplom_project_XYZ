#include "AttackComponent.h"

#include "Vector.h"

#include <cassert>
namespace XYZRoguelike {
AttackComponent::AttackComponent(XYZEngine::GameObject* gameObject)
    : Component(gameObject) {
    weapon = gameObject->GetComponent<Weapon>();
    assert(weapon != nullptr && "Weapon object must not be null");
}

void AttackComponent::Update(float deltaTime) {
    delayAttack -= 1.f * deltaTime;
    if (delayAttack <= 0.f) {
        weapon->SetActive(false);
        attackSpeed -= 1.f * deltaTime;
    }
}

void AttackComponent::Render() {}

void AttackComponent::Attack() {
    if (delayAttack <= 0.f && attackSpeed <= 0.f) {
        delayAttack = weapon->GetDelayAttack();
        attackSpeed = weapon->GetAttackSpeed();
        weapon->SetActive(true);
    }
}

}  // namespace XYZRoguelike