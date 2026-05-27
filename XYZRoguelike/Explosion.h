#pragma once
#include "CharacterStatsComponent.h"
#include "Component.h"
#include "GameWorld.h"
#include "InputComponent.h"
#include "SpriteRendererComponent.h"
#include "Weapon.h"

#include <ResourceSystem.h>
namespace XYZRoguelike {
class Explosion : public Weapon {
   public:
    Explosion(XYZEngine::GameObject* gameObject);
    ~Explosion();
    void Update(float deltaTime) override;
    void Render() override;
    void SetActive(bool OnActive) override;
    void DamageCollision(XYZEngine::Collision collision) override;

   private:
    XYZEngine::SpriteRendererComponent* objectRenderer;
    XYZEngine::GameObject* ownerObject;
    XYZEngine::TransformComponent* explosionTransform;
    float placementDistance = 40.f;
    const float DamageDistance = 70.f;
    float explosionDamage = 35.f;
    float tickDamage = 0.f;
};
}  // namespace XYZRoguelike