#include "FireBall.h"
#include "CharacterStatsComponent.h"
#include "GameWorld.h"
#include "ResourceSystem.h"

namespace XYZRoguelike {
FireBall::FireBall(XYZEngine::GameObject* gameObject) : Weapon(gameObject) 
{
    ownerTransform = gameObject->GetComponent<XYZEngine::TransformComponent>();
    weaponObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Fireball");

    projectile = weaponObject->AddComponent<XYZEngine::ProjectileMovementComponent>();
    projectile->SetSpeed(65.f);
    fireballRenderer =
        weaponObject->AddComponent<XYZEngine::SpriteRendererComponent>();
    fireballRenderer->SetTexture(
        *XYZEngine::ResourceSystem::Instance()->GetTextureShared("Fireball"));
    fireballRenderer->SetPixelSize(0, 0);
    body = weaponObject->AddComponent<XYZEngine::RigidbodyComponent>();
    body->SetKinematic(true);
    transform = weaponObject->GetComponent<XYZEngine::TransformComponent>();
    transform->SetWorldPosition(ownerTransform->GetWorldPosition());
}
FireBall::~FireBall() {}
void FireBall::Update(float deltaTime) {
    if (projectile->GetLifeTime() <= 0.f && collider) 
    {
        collider->UnsubscribeCollision(
            std::bind(&FireBall::DamageCollision,
                                                 this, std::placeholders::_1));
        weaponObject->RemoveComponent(collider);
        collider = nullptr;
        fireballRenderer->SetPixelSize(0, 0); 
    }
}
void FireBall::Render() {}
void FireBall::SetActive(bool OnActive) {
    collider = weaponObject->AddComponent<XYZEngine::SpriteColliderComponent>();
    fireballRenderer->SetPixelSize(43, 43);
    projectile->SetLifeTime(lifeTime);
    collider->SubscribeCollision(
        std::bind(&FireBall::DamageCollision, this, std::placeholders::_1));
}
void XYZRoguelike::FireBall::DamageCollision(XYZEngine::Collision collision) {
    auto characterStats = collision.first->GetGameObject()
                              ->GetComponent<CharacterStatsComponent>();
   
    if (characterStats && collision.first->GetGameObject() != gameObject) 
    {
        characterStats->DealDamage(fireballDamage);
    }

    collider->UnsubscribeCollision(
        std::bind(&FireBall::DamageCollision, this, std::placeholders::_1));
    weaponObject->RemoveComponent(collider);
    collider = nullptr;
    fireballRenderer->SetPixelSize(0, 0); 
    
}

void FireBall::SetDirectional(XYZEngine::Vector2Df newDirection) 
{
    projectile->SetDirection(newDirection);
}

void FireBall::SetPosition(XYZEngine::Vector2Df newPosition) 
{
    transform->SetWorldPosition(newPosition);
}

}  // namespace XYZRoguelike