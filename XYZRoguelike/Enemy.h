#pragma once

#include "AISwordMan.h"
#include "GameSettings.h"
#include "CharacterStatsComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "RenderSystem.h"
#include "Weapon.h"

#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>

namespace XYZRoguelike {
template<typename AI, typename Weapon> class Enemy {
   public:
    Enemy() {
        gameObject =
            XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");
        auto playerRenderer =
            gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
        playerRenderer->SetTexture(
            *XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
        playerRenderer->SetPixelSize(24, 24);
        auto transform =
            gameObject->GetComponent<XYZEngine::TransformComponent>();
        auto weapon = gameObject->AddComponent<Weapon>();
        auto attackSystem = gameObject->AddComponent<AttackComponent>();
        auto movement = gameObject->AddComponent<AI>();
        movement->SetTarget(
            XYZEngine::GameWorld::Instance()->GetGameObjectByName(GameSettings::Instance()->PLAYER_NAME));
        auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
        auto collider =
            gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
        movement->GetGameObject()->AddChild(collider->GetGameObject());
        auto enemyStats = gameObject->AddComponent<CharacterStatsComponent>();
    }

    Enemy(const XYZEngine::Vector2Df position, const std::string name) {
        gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject(name);
        auto playerRenderer =
            gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
        playerRenderer->SetTexture(
            *XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
        playerRenderer->SetPixelSize(24, 24);
        auto transform =
            gameObject->GetComponent<XYZEngine::TransformComponent>();
        transform->SetWorldPosition(position);
        auto weapon = gameObject->AddComponent<Weapon>();
        auto attackSystem = gameObject->AddComponent<AttackComponent>();
        auto movement = gameObject->AddComponent<AI>();
        movement->SetTarget(
            XYZEngine::GameWorld::Instance()->GetGameObjectByName(
                GameSettings::Instance()->PLAYER_NAME));
        auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
        auto collider =
            gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
        auto enemyStats = gameObject->AddComponent<CharacterStatsComponent>();
        enemyStats->SetHealth(15.f);
    }

    XYZEngine::GameObject* GetGameObject() { return gameObject; }

   private:
    XYZEngine::GameObject* gameObject;
};
}  // namespace XYZRoguelike
