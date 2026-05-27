#include "Sword.h"

#include "CharacterStatsComponent.h"
#include "Logger.h"

#include <ResourceSystem.h>
namespace XYZRoguelike {
Sword::Sword(XYZEngine::GameObject* gameObject) : Weapon(gameObject) {
    ownerTransform = gameObject->GetComponent<XYZEngine::TransformComponent>();
    weaponObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Sword");

    swordRenderer =
        weaponObject->AddComponent<XYZEngine::SpriteRendererComponent>();
    swordRenderer->SetTexture(
        *XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
    swordRenderer->SetPixelSize(0, 0);
    body = weaponObject->AddComponent<XYZEngine::RigidbodyComponent>();
    body->SetKinematic(true);
    transform = weaponObject->GetComponent<XYZEngine::TransformComponent>();
    transform->SetWorldPosition({0.f, 0.f});
}
Sword::~Sword() {
}

void Sword::Update(float deltaTime) {
    if (tickDamage > 0.f) {
        tickDamage -= 1.f * deltaTime;
    }
    if (ownerTransform) {
        auto characterPosition = ownerTransform->GetWorldPosition();
        auto characterRotation = ownerTransform->GetWorldRotation();

        float dirX = cos(transform->GetWorldRotation() * 3.14159265f /
                         180.f);  // Переводим в радианы
        float dirY = sin(transform->GetWorldRotation() * 3.14159265f / 180.f);

        XYZEngine::Vector2Df offset;
        offset.x = characterPosition.x + dirX * placementDistance;
        offset.y = characterPosition.y + dirY * placementDistance;

        transform->SetWorldRotation(characterRotation);
        transform->SetWorldPosition(offset);
    }
}

void Sword::Render() {}

void Sword::SetActive(bool OnActive) {
    if (OnActive) {
        collider =
            weaponObject->AddComponent<XYZEngine::SpriteColliderComponent>();
        collider->SubscribeCollision(
            std::bind(&Sword::DamageCollision, this, std::placeholders::_1));
        swordRenderer->SetPixelSize(35, 8);
    } else if (collider != nullptr) {
        collider->UnsubscribeCollision(
            std::bind(&Sword::DamageCollision, this, std::placeholders::_1));

        weaponObject->RemoveComponent(collider);
        collider = nullptr;
        swordRenderer->SetPixelSize(0, 0);
    }
}

void Sword::DamageCollision(XYZEngine::Collision collision) {
    auto characterStats =
        collision.first->GetGameObject()->GetComponent<CharacterStatsComponent>();
    try {
        if (!characterStats) {
            throw std::invalid_argument(
                "Component: CharacterStatsComponent not found\n");
        }
    } catch (const std::invalid_argument& e) {
        LOG_WARN(e.what());
    }
    if (characterStats && (tickDamage <= 0.f && tickDamage <= 0.f)) {
        characterStats->DealDamage(swordDamage);
        tickDamage = 1.f;
        std::cout << characterStats->GetHealth() << std::endl;
    }
}
}  // namespace XYZRoguelike