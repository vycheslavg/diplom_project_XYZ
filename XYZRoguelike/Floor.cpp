#include "Floor.h"

XYZRoguelike::Floor::Floor(const XYZEngine::Vector2Df position,
                           int textureMapIndex) {
    gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Floor");
    transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    auto renderer =
        gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
    renderer->SetTexture(
        *XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared(
            "Floors", textureMapIndex));
    renderer->SetPixelSize(64, 64);
}
