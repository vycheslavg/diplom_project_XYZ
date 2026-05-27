#pragma once
#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"
namespace XYZRoguelike {
class CharacterStatsComponent : public XYZEngine::Component {
   public:
    CharacterStatsComponent(XYZEngine::GameObject* gameObject);
    void SetMaxHealth(float maxHealthSet);
    void SetHealth(float healthSet);
    float GetHealth();
    void SetArmor(float armorSet);
    void DealDamage(float amountDamage);
    bool CheckStateLifeCharacter();
    void RestoreHealth(float amountHealth);
    void OnDeath();

    virtual void Update(float deltaTime) override;
    virtual void Render() override;

   private:
    float health, maxHealth, armor;
    bool stateLifeCharacter = true;
};
}  // namespace XYZRoguelike