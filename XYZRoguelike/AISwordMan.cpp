#include "AISwordMan.h"

#include "CharacterStatsComponent.h"
#include "Logger.h"
namespace XYZRoguelike {
AISwordMan::AISwordMan(XYZEngine::GameObject* gameObject)
    : XYZEngine::AIMovementComponent(gameObject) {
    transformSelf = gameObject->GetComponent<XYZEngine::TransformComponent>();
    attackComponent = gameObject->GetComponent<AttackComponent>();
    speed = 20.f;
    viewingRadius = 300.f;
    previousPosition = {0, 0};
    acceleration = {0, 0};
}
void AISwordMan::Update(float deltaTime) {
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
        attackComponent->Attack();
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

}  // namespace XYZRoguelike