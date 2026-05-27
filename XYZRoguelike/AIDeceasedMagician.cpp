#include "AIDeceasedMagician.h"
#include "CharacterStatsComponent.h"
#include "GameSettings.h"
#include <ResourceSystem.h>
namespace XYZRoguelike {

AIDeceasedMagician::AIDeceasedMagician(XYZEngine::GameObject* gameObject)
    : XYZEngine::AIMovementComponent(gameObject) {
    selfObject = gameObject;
    auto mageRenderer =
        gameObject->GetComponent<XYZEngine::SpriteRendererComponent>();
    mageRenderer->SetTexture(
        *XYZEngine::ResourceSystem::Instance()->GetTextureShared(
            "DeceasedMagician"));
    objectTransform = gameObject->GetComponent<XYZEngine::TransformComponent>();
    mageRenderer->SetPixelSize(60, 60);
    transformSelf = gameObject->GetComponent<XYZEngine::TransformComponent>();
    fireballUp = selfObject->AddComponent<FireBall>();
    fireballDown = selfObject->AddComponent<FireBall>();
    fireballRight = selfObject->AddComponent<FireBall>();
    fireballLeft = selfObject->AddComponent<FireBall>();
    speed = 120.f;
    viewingRadius = 600.f;
    previousPosition = {0, 0};
    acceleration = {0, 0};
}

void AIDeceasedMagician::Update(float deltaTime) 
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

    if (distanceFromTarget <= dangerousDistance && teleportRollback <= 0.f) {
        std::srand(std::time(nullptr));
        int widthMap = (GameSettings::Instance()->MAP_WIDTH - 3.f) *
                         GameSettings::Instance()->BLOCK_SIZE;
        int heightMap = (GameSettings::Instance()->MAP_HEIGHT - 3.f) *
                          GameSettings::Instance()->BLOCK_SIZE;
        XYZEngine::Vector2Df randomTeleportation = {
            static_cast<float>(std::rand() % widthMap),
            static_cast<float>(std::rand() % heightMap)
        };
        objectTransform->SetWorldPosition(randomTeleportation);
        teleportRollback = 8.0f;
        return;
    }
    teleportRollback -= 1.f * deltaTime;

    transformSelf->RotateTo(transformSelf->GetWorldPosition(),
                            targetTransform->GetWorldPosition());

    
    if (AttackSpeed <= 0.f) {
        fireballUp->SetDirectional({0, 1});
        fireballUp->SetPosition({objectTransform->GetWorldPosition().x,
                                 objectTransform->GetWorldPosition().y + 75.f});
        fireballUp->SetActive(true);

        fireballDown->SetDirectional({0, -1});
        fireballDown->SetPosition(
            {objectTransform->GetWorldPosition().x,
             objectTransform->GetWorldPosition().y - 75.f});
        fireballDown->SetActive(true);

        fireballRight->SetDirectional({1, 0});
        fireballRight->SetPosition(
            {objectTransform->GetWorldPosition().x + 75.f,
             objectTransform->GetWorldPosition().y});
        fireballRight->SetActive(true);

        fireballLeft->SetDirectional({-1, 0});
        fireballLeft->SetPosition({objectTransform->GetWorldPosition().x - 75.f,
                                   objectTransform->GetWorldPosition().y});
        fireballLeft->SetActive(true);
        AttackSpeed = 3.f;
        return;
    }
    AttackSpeed -= 1.f * deltaTime;

    acceleration = transformSelf->GetWorldPosition() - previousPosition;
    previousPosition = transformSelf->GetWorldPosition();
}

}  // namespace XYZRoguelike
