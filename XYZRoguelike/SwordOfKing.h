#pragma once
#include "Component.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"
#include "Weapon.h"

#include <SpriteColliderComponent.h>
namespace XYZRoguelike {
class SwordOfKing : public Weapon {
   public:
    SwordOfKing(XYZEngine::GameObject* gameObject);
    ~SwordOfKing();
    void Update(float deltaTime) override;
    void Render() override;
    void SetActive(bool OnActive) override;
    void DamageCollision(XYZEngine::Collision collision) override;

   protected:
    XYZEngine::SpriteRendererComponent* swordRenderer;
    XYZEngine::TransformComponent* transform;
    XYZEngine::TransformComponent* ownerTransform;
    XYZEngine::SpriteColliderComponent* collider;
    XYZEngine::RigidbodyComponent* body;
    bool activeAttack = false;
    float placementDistance = 135.f;
    float swordDamage = 35.f;
    float swingTime = 2.5f;
    float tickDamage = 0.f;
};
}  // namespace XYZRoguelike