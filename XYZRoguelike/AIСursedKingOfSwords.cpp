#include "AIÑursedKingOfSwords.h"
#include "CharacterStatsComponent.h"
#include "SwordOfKing.h"
#include "AttackComponent.h"
#include <ResourceSystem.h>

namespace XYZRoguelike 
{
AIÑursedKingOfSwords::AIÑursedKingOfSwords(XYZEngine::GameObject* gameObject)
    : XYZEngine::AIMovementComponent(gameObject) {
    auto kingRenderer =
        gameObject->GetComponent<XYZEngine::SpriteRendererComponent>();
    kingRenderer->SetTexture(
        *XYZEngine::ResourceSystem::Instance()->GetTextureShared(
            "KingOfSwords"));
    kingRenderer->SetPixelSize(74, 74);
    auto sword = gameObject->AddComponent<SwordOfKing>();
    auto attackComponent = gameObject->AddComponent<AttackComponent>();
    transformSelf = gameObject->GetComponent<XYZEngine::TransformComponent>();
    speed = 90.f;
    viewingRadius = 600.f;
    previousPosition = {0, 0};
    acceleration = {0, 0};
}
void AIÑursedKingOfSwords::Update(float deltaTime) 
{
    XYZEngine::Vector2Df positionAI = transformSelf->GetWorldPosition();
    if (!objectTarget) {
        return;
    }

    auto characterStats = objectTarget->GetComponent<CharacterStatsComponent>();
    if (!characterStats || !characterStats->CheckStateLifeCharacter()) {
        objectTarget = nullptr;
        return;
    }

    auto targetTransform =
        objectTarget->GetComponent<XYZEngine::TransformComponent>();
    float distanceFromTarget =
        positionAI.CalculateDistance(targetTransform->GetWorldPosition());

    if (distanceFromTarget > viewingRadius) {
        return;
    }

    transformSelf->RotateTo(transformSelf->GetWorldPosition(),
                            targetTransform->GetWorldPosition());

    if (distanceFromTarget <= meleeAttackRadius) {
        gameObject->GetComponent<AttackComponent>()->Attack();
        return;
    }

    XYZEngine::Vector2Df direction =
        targetTransform->GetWorldPosition() - transformSelf->GetWorldPosition();
    direction = direction.Normalize();

    transformSelf->MoveBy(speed * deltaTime *
                          XYZEngine::Vector2Df{direction.x, direction.y});

    acceleration = transformSelf->GetWorldPosition() - previousPosition;
    previousPosition = transformSelf->GetWorldPosition();
}
}