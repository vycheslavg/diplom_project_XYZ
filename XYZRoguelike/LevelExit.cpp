
#include "GameSettings.h"

#include "LevelExit.h"
#include "LevelManager.h"
#include "InventoryComponent.h"
#include <GameWorld.h>
#include <SpriteColliderComponent.h>
#include <RigidbodyComponent.h>
#include <ResourceSystem.h>

namespace XYZRoguelike {
LevelExit::LevelExit(const XYZEngine::Vector2Df position) {
    gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Exit");
    auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
    body->SetKinematic(true);
    auto renderer =
        gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
    renderer->SetTexture(
        *XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
    renderer->SetPixelSize(64, 64);
    auto collider =
        gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
    auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
    transform->SetWorldPosition(position);
    collider->SubscribeCollision(
        std::bind(&LevelExit::Transition, this, std::placeholders::_1));
}

void LevelExit::Transition(XYZEngine::Collision collision) {
    if (collision.first->GetGameObject()->GetComponent<InventoryComponent>() !=
            nullptr &&
        collision.first->GetGameObject()
                ->GetComponent<InventoryComponent>()
                ->GetKey() != 0) 
    {
        collision.first->GetGameObject()
            ->GetComponent<InventoryComponent>()
            ->UseKey();
        isDoorClosed = false;
    }

    // XYZEngine::GameWorld::Instance()->DestroyGameObject(this->gameObject);
    if (!isDoorClosed) {
        LevelManager::Instance()->LoadRandomLevels();
    }
    //}
}
XYZEngine::GameObject* LevelExit::GetGameObject() { return gameObject; }

void LevelExit::SetIsDoorClosed(bool isClosed) { isDoorClosed = isClosed; }

}  // namespace XYZRoguelike