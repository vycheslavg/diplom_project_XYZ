#include "CharacterStatsComponent.h"
#include <SFML/Graphics.hpp>
#include "ItemDropComponent.h"
#include "GameWorld.h"
#include "Logger.h"
#include "Weapon.h"
#include <string>
#include "RenderSystem.h"

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

void CharacterStatsComponent::Render() {

    // Рисуем HP ТОЛЬКО для игрока
    if (gameObject->GetName() != "Player")
        return;

    static sf::Font font;
    static bool loaded = false;

    if (!loaded) {
        font.loadFromFile("Resources/Fonts/Roboto-Light.ttf");
        loaded = true;
    }

    int lives = 0;

    if (health >= 100.f)
        lives = 4;
    else if (health >= 75.f)
        lives = 3;
    else if (health >= 50.f)
        lives = 2;
    else if (health >= 25.f)
        lives = 1;
    else
        lives = 1;

    sf::Text hpText;

    hpText.setFont(font);
    hpText.setCharacterSize(40);
    hpText.setFillColor(sf::Color::White);

    hpText.setString("HP: " + std::to_string(lives));

    hpText.setPosition(1100.f, 20.f);

    auto& window = XYZEngine::RenderSystem::Instance()->GetMainWindow();

    sf::View currentView = window.getView();

    window.setView(window.getDefaultView());

    window.draw(hpText);

    window.setView(currentView);
}

void CharacterStatsComponent::OnDeath() {
    if(gameObject->GetComponent<ItemDropComponent>())
    {
        gameObject->GetComponent<ItemDropComponent>()->Drop();
    }
    health = 0.f;
    LOG_INFO("Dead");
    stateLifeCharacter = false;
}

}  // namespace XYZRoguelike