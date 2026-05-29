#pragma once
#include "InitializeNPCSpawnerComponent.h"
#include "SpawnerComponent.h"
#include "SpriteRendererComponent.h"

#include <GameObject.h>
#include <GameWorld.h>
#include <ResourceSystem.h>

namespace XYZRoguelike {
template<typename NPC> class NPCSpawner {
   public:
    NPCSpawner(const XYZEngine::Vector2Df& position, float spawnInterval,
               float maxSpawn, bool isEndless,
               std::string uniqueNameSpawnObject) {
        gameObject =
            XYZEngine::GameWorld::Instance()->CreateGameObject("NPCSpawner");
        auto playerRenderer =
            gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
        playerRenderer->SetTexture(
            *XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
        playerRenderer->SetPixelSize(24, 24);
        auto transform =
            gameObject->GetComponent<XYZEngine::TransformComponent>();
        transform->SetWorldPosition(position);
        auto initializeSpawner =
            gameObject->AddComponent<InitializeNPCSpawnerComponent>();
        initializeSpawner->Initialize(spawnInterval, maxSpawn, isEndless,
                                      uniqueNameSpawnObject);
        auto spawner = gameObject->AddComponent<SpawnerComponent<NPC>>();
    }

    XYZEngine::GameObject* GetGameObject() const { return gameObject; }

   private:
    XYZEngine::GameObject* gameObject;
};
}  // namespace XYZRoguelike
