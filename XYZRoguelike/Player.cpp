#include "Player.h"
#include "GameSettings.h"

#include "AttackComponent.h"
#include "CharacterStatsComponent.h"
#include "ControllerInputComponent.h"
#include "Explosion.h"
#include "Sword.h"

#include <MovementComponent.h>
#include <ResourceSystem.h>
#include <SpriteDirectionComponent.h>
#include <SpriteColliderComponent.h>
#include <SpriteMovementAnimationComponent.h>

namespace XYZRoguelike {
Player::Player(const XYZEngine::Vector2Df& position) {
    gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject(GameSettings::Instance()->PLAYER_NAME);
   auto playerRenderer =
        gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
    playerRenderer->SetTexture(
        *XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared(
            "player", 0));
    playerRenderer->SetPixelSize(32, 32);
    auto playerCamera = gameObject->AddComponent<XYZEngine::CameraComponent>();
    playerCamera->SetWindow(
        &XYZEngine::RenderSystem::Instance()->GetMainWindow());
    playerCamera->SetBaseResolution(1280, 720);
    playerCamera->SetTurnTracking(false);

    auto playerInput = gameObject->AddComponent<XYZEngine::InputComponent>();

    auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    auto movement = gameObject->AddComponent<XYZEngine::MovementComponent>();
    movement->SetSpeed(400.f);
    movement->SetDirectionalRotation(true);

    auto spriteDirection =
        gameObject->AddComponent<XYZEngine::SpriteDirectionComponent>();

    auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
    auto weapon = gameObject->AddComponent<Sword>();

    auto attackSystem = gameObject->AddComponent<AttackComponent>();
    auto controllerInput = gameObject->AddComponent<ControllerInputComponent>();

    auto collider =
        gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
    auto animator = gameObject->AddComponent<XYZEngine::SpriteMovementAnimationComponent>();
    animator->Initialize("player", 6.f);
    auto playerStats = gameObject->AddComponent<CharacterStatsComponent>();
    playerStats->SetArmor(4.f);
}

XYZEngine::GameObject* Player::GetGameObject() { return gameObject; }


}  // namespace XYZRoguelike