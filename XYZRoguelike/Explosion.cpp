#include "Explosion.h"

#include "AIMovementComponent.h"
#include "Logger.h"
namespace XYZRoguelike {
Explosion::Explosion(XYZEngine::GameObject* gameObject) : Weapon(gameObject) {
    ownerObject = gameObject;
    weaponObject =
        XYZEngine::GameWorld::Instance()->CreateGameObject("Explosion");

    explosionTransform =
        weaponObject->GetComponent<XYZEngine::TransformComponent>();
    explosionTransform->SetWorldPosition({0.f, 0.f});

    objectRenderer =
        weaponObject->AddComponent<XYZEngine::SpriteRendererComponent>();
    objectRenderer->SetTexture(
        *XYZEngine::ResourceSystem::Instance()->GetTextureShared("Explosion"));
    objectRenderer->SetPixelSize(0, 0);
}
Explosion::~Explosion() {}
void Explosion::Update(float deltaTime) {
    if (tickDamage > 0.f) {
        tickDamage -= 1.f * deltaTime;
    }
}
void Explosion::Render() {}
void Explosion::SetActive(bool OnActive) {
    if (OnActive) {
        explosionTransform->SetWorldPosition(
            ownerObject->GetComponent<XYZEngine::TransformComponent>()
                ->GetWorldPosition());
        objectRenderer->SetPixelSize(90, 90);
        XYZEngine::Vector2Df positionAI =
            gameObject->GetComponent<XYZEngine::TransformComponent>()
                ->GetWorldPosition();
        auto targetTransform =
            ownerObject->GetComponent<XYZEngine::AIMovementComponent>()
                ->GetTarget()
                ->GetComponent<XYZEngine::TransformComponent>();
        if (!targetTransform) {
            return;
        }
        float distanceFromTarget =
            positionAI.CalculateDistance(targetTransform->GetWorldPosition());

        if (distanceFromTarget <= DamageDistance) {
            auto targetCharacterStats =
                ownerObject->GetComponent<XYZEngine::AIMovementComponent>()
                    ->GetTarget()
                    ->GetComponent<CharacterStatsComponent>();
            if (targetCharacterStats) {
                targetCharacterStats->DealDamage(explosionDamage);
            }
        }
    } else {
        objectRenderer->SetPixelSize(0, 0);
    }
}
void Explosion::DamageCollision(XYZEngine::Collision collision) {}
}  // namespace XYZRoguelike