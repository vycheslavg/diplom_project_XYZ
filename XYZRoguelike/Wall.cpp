#include "Wall.h"

#include <MovementComponent.h>
#include <SpriteColliderComponent.h>

Wall::Wall(const XYZEngine::Vector2Df position, int indexTexture) {
    gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Wall");
    transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    auto renderer =
        gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
    renderer->SetTexture(
        *XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared(
            "Walls", indexTexture));
    renderer->SetPixelSize(64, 64);

    auto rigidbody = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
    rigidbody->SetKinematic(true);

    auto collider =
        gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
}
