#pragma once
#include "Weapon.h" 
#include "ProjectileMovementComponent.h"

namespace XYZRoguelike
{
class FireBall : public Weapon 
{
   public:
    FireBall(XYZEngine::GameObject* gameObject);
    ~FireBall();
    void Update(float deltaTime) override;
    void Render() override;
    void SetActive(bool OnActive) override;
    void DamageCollision(XYZEngine::Collision collision) override;
    void SetDirectional(XYZEngine::Vector2Df newDirection);
    void SetPosition(XYZEngine::Vector2Df newPosition);

   private:
    XYZEngine::SpriteRendererComponent* fireballRenderer;
    XYZEngine::TransformComponent* transform;
    XYZEngine::TransformComponent* ownerTransform;
    XYZEngine::SpriteColliderComponent* collider;
    XYZEngine::ProjectileMovementComponent* projectile;
    XYZEngine::RigidbodyComponent* body;
    XYZEngine::Vector2Df directionFireball = {0.f, 0.f};
    float lifeTime = 2.5f;
    float fireballDamage = 30.f;
};
}  // namespace XYZRoguelike