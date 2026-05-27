#include "CharacterStatsComponent.h"

#include "GameWorld.h"
#include "Logger.h"
#include "Weapon.h"

namespace XYZRoguelike {

CharacterStatsComponent::CharacterStatsComponent(XYZEngine::GameObject* gameObject)
    : Component(gameObject) {
    health = 100.f;
    maxHealth = 100.f;
    armor = 0.f;
}

void CharacterStatsComponent::SetMaxHealth(float maxHealthSet) {
    maxHealth = maxHealthSet;
}

void CharacterStatsComponent::SetHealth(float healthSet) { health = healthSet; }

float CharacterStatsComponent::GetHealth() { return health; }

void CharacterStatsComponent::SetArmor(float armorSet) { armor = armorSet; }

void CharacterStatsComponent::DealDamage(float amountDamage) {
    if (std::abs(amountDamage) <= armor) {
        LOG_INFO("The armor absorbed all the damage\n");
        return;
    }
    if (health >= std::abs(amountDamage) - armor) {
        LOG_INFO(this->gameObject->GetName() + " received damage: " +
                 std::to_string(std::abs(amountDamage) - armor) + "\n");
        health -= std::abs(amountDamage) - armor;
    } else {
        OnDeath();
    }
}

bool CharacterStatsComponent::CheckStateLifeCharacter() { return stateLifeCharacter; }

void CharacterStatsComponent::RestoreHealth(float amountHealth) {
    health += amountHealth;
}

void CharacterStatsComponent::Update(float deltaTime) {
    if (!stateLifeCharacter) {
        if (this->gameObject->GetComponent<Weapon>())
        {
            XYZEngine::GameWorld::Instance()->DestroyGameObject(
                this->gameObject->GetComponent<Weapon>()->GetWeaponObject());
        }
        XYZEngine::GameWorld::Instance()->DestroyGameObject(this->gameObject);
    }
}

void CharacterStatsComponent::Render() {}

void CharacterStatsComponent::OnDeath() {
    health = 0.f;
    LOG_INFO("Dead");
    stateLifeCharacter = false;
}

}  // namespace XYZRoguelike