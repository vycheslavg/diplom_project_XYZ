#pragma once

#include "AIÑursedKingOfSwords.h"
#include "CharacterStatsComponent.h"
#include "GameObject.h"
#include "GameSettings.h"
#include "GameWorld.h"
#include "RenderSystem.h"
#include "ItemDropComponent.h"
#include "Weapon.h"

#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>

namespace XYZRoguelike {
template<typename AIBoss> class Boss {
   public:
    Boss(const XYZEngine::Vector2Df position, const std::string name) {
        gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject(name);
        auto BossRenderer =
            gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
        auto transform =
            gameObject->GetComponent<XYZEngine::TransformComponent>();
        transform->SetWorldPosition(position);
        auto movement = gameObject->AddComponent<AIBoss>();
        movement->SetTarget(
            XYZEngine::GameWorld::Instance()->GetGameObjectByName(
                GameSettings::Instance()->PLAYER_NAME));
        auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
        auto collider =
            gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

        auto drop = gameObject->AddComponent<ItemDropComponent>();

        auto enemyStats = gameObject->AddComponent<CharacterStatsComponent>();
        enemyStats->SetHealth(160.f);
    }
    XYZEngine::GameObject* GetGameObject() { return gameObject; }

   private:
    XYZEngine::GameObject* gameObject;
};
}  // namespace XYZRoguelike
