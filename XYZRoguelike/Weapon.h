#pragma once
#include "Component.h"
#include "GameObject.h"

#include <SpriteColliderComponent.h>
namespace XYZRoguelike {
class Weapon : public XYZEngine::Component {
   public:
    Weapon(XYZEngine::GameObject* gameObject)
        : XYZEngine::Component(gameObject) {};
    virtual void SetActive(bool OnActive) = 0;
    virtual void DamageCollision(XYZEngine::Collision collision) = 0;
    float GetDelayAttack() { return delayAttack; };
    float GetAttackSpeed() { return attackSpeed; };
    XYZEngine::GameObject* GetWeaponObject() {
        return weaponObject;
    }
   protected:
    XYZEngine::GameObject* weaponObject = nullptr;
    float delayAttack = 0.1f;
    float attackSpeed = 2.f;
};
}  // namespace XYZRoguelike