#include "SwordOfKing.h"

#include "CharacterStatsComponent.h"
#include "Logger.h"

#include <ResourceSystem.h>
#include <cassert>
#include <stdexcept>

namespace XYZRoguelike {

SwordOfKing::SwordOfKing(XYZEngine::GameObject* gameObject)
    : Weapon(gameObject) {
    delayAttack = 4.f;

    tickDamage = 0.2f;

    ownerTransform = gameObject->GetComponent<XYZEngine::TransformComponent>();

    weaponObject =
        XYZEngine::GameWorld::Instance()->CreateGameObject("SwordOfKing");

    swordRenderer =
        weaponObject->AddComponent<XYZEngine::SpriteRendererComponent>();

    swordRenderer->SetTexture(
        *XYZEngine::ResourceSystem::Instance()->GetTextureShared(
            "ShadowOfSword"));

    swordRenderer->SetPixelSize(0, 0);

    body = weaponObject->AddComponent<XYZEngine::RigidbodyComponent>();

    body->SetKinematic(true);

    transform = weaponObject->GetComponent<XYZEngine::TransformComponent>();

    transform->SetWorldPosition({0.f, 0.f});
}

SwordOfKing::~SwordOfKing() {}

void SwordOfKing::Update(float deltaTime) {
    if (tickDamage > 0.f) {
        tickDamage -= 1.f * deltaTime;
    }

    if (ownerTransform) {
        auto characterPosition = ownerTransform->GetWorldPosition();

        auto characterRotation = ownerTransform->GetWorldRotation();

        float dirX = cos(transform->GetWorldRotation() * 3.14159265f / 180.f);

        float dirY = sin(transform->GetWorldRotation() * 3.14159265f / 180.f);

        XYZEngine::Vector2Df offset;

        offset.x = characterPosition.x + dirX * placementDistance;

        offset.y = characterPosition.y + dirY * placementDistance;

        transform->SetWorldRotation(characterRotation);

        transform->SetWorldPosition(offset);
    }

    if (activeAttack) {
        swordRenderer->SetTexture(
            *XYZEngine::ResourceSystem::Instance()->GetTextureShared(
                "ShadowOfSword"));

        swordRenderer->SetPixelSize(130, 90);

        swingTime -= 1.f * deltaTime;

        if (swingTime <= 0.f) {
            swordRenderer->SetTexture(
                *XYZEngine::ResourceSystem::Instance()->GetTextureShared(
                    "SwordOfKing"));

            swordRenderer->SetPixelSize(150, 100);

            collider = weaponObject
                           ->AddComponent<XYZEngine::SpriteColliderComponent>();

            collider->SubscribeCollision(std::bind(
                &SwordOfKing::DamageCollision, this, std::placeholders::_1));

            activeAttack = false;
        }
    }
}

void SwordOfKing::Render() {}

void SwordOfKing::SetActive(bool OnActive) {
    if (OnActive) {
        activeAttack = true;
    } else if (collider != nullptr && !OnActive) {
        collider->UnsubscribeCollision(std::bind(&SwordOfKing::DamageCollision,
                                                 this, std::placeholders::_1));

        weaponObject->RemoveComponent(collider);

        collider = nullptr;

        swordRenderer->SetPixelSize(0, 0);

        swingTime = 2.5f;
    }
}

void SwordOfKing::DamageCollision(XYZEngine::Collision collision) {
    auto firstObject = collision.first->GetGameObject();

    auto secondObject = collision.second->GetGameObject();

    auto target = firstObject == weaponObject ? secondObject : firstObject;

    // защита владельца от собственного урона
    if (target == gameObject) {
        return;
    }

    auto characterStats = target->GetComponent<CharacterStatsComponent>();

    try {
        if (!characterStats) {
            throw std::invalid_argument(
                "Component: CharacterStatsComponent not found\n");
        }

        assert(characterStats != nullptr);

        if (tickDamage <= 0.f) {
            characterStats->DealDamage(swordDamage);

            tickDamage = 1.f;

            std::cout << characterStats->GetHealth() << std::endl;
        }
    } catch (const std::exception& e) {
        LOG_WARN(e.what());
    }
}

}  // namespace XYZRoguelike