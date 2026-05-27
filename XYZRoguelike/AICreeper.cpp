#include "AICreeper.h"

#include "CharacterStatsComponent.h"
#include "Logger.h"

namespace XYZRoguelike {
AICreeper::AICreeper(XYZEngine::GameObject* gameObject)
    : XYZEngine::AIMovementComponent(gameObject) {
    transformSelf = gameObject->GetComponent<XYZEngine::TransformComponent>();
    attackComponent = gameObject->GetComponent<AttackComponent>();
    speed = 200.f;
    viewingRadius = 350.f;
    previousPosition = {0, 0};
    acceleration = {0, 0};
}

void AICreeper::Update(float deltaTime) {
    if (gapBetweenMoving > 0.f) {
        gapBetweenMoving -= 1.f * deltaTime;
        return;
    }

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

    if (distanceFromTarget <= meleeAttackRadius || isExplosionStarted == true) {
        isExplosionStarted = true;
        delayAttack -= 1.f * deltaTime;
        if (delayAttack <= 0.f) {
            auto CreeperStats =
                this->gameObject->GetComponent<CharacterStatsComponent>();
            attackComponent->Attack();
            transformSelf->SetWorldScale(
                0.f, 0.f);  // Removing the visual representation of the object
            if (timeExplosion <= 0) {
                gameObject->GetComponent<CharacterStatsComponent>()->OnDeath();
                return;
            } else {
                timeExplosion -= 1.f * deltaTime;
            }
        }
        return;
    }

    XYZEngine::Vector2Df direction =
        targetTransform->GetWorldPosition() - transformSelf->GetWorldPosition();
    direction = direction.Normalize();

    transformSelf->MoveBy(speed * deltaTime *
                          XYZEngine::Vector2Df{direction.x, direction.y});

    acceleration = transformSelf->GetWorldPosition() - previousPosition;
    previousPosition = transformSelf->GetWorldPosition();

    if (timeMoving > 0.f) {
        timeMoving -= 1.f * deltaTime;
        return;
    }

    gapBetweenMoving = GAP_BETWEEN_MOVING;
    timeMoving = TIME_MOVING;
}

}  // namespace XYZRoguelike