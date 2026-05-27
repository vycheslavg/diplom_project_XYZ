#pragma once
#include "Component.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "InputComponent.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"
#include "Weapon.h"

#include <SpriteColliderComponent.h>
namespace XYZRoguelike {
class Sword : public Weapon {
   public:
    Sword(XYZEngine::GameObject* gameObject);
    ~Sword();
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
    float placementDistance = 40.f;
    float swordDamage = 25.f;
    float tickDamage = 0.f;
};

}  // namespace XYZRoguelike