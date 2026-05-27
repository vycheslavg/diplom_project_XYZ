#pragma once

#include "AISwordMan.h"
#include "Enemy.h"
#include "Floor.h"
#include "LevelExit.h"
#include "NPCSpawner.h"
#include "Player.h"
#include "Boss.h"
#include "GameSettings.h"
#include "Scene.h"
#include "SoundPlayer.h"
#include "Wall.h"

#include <array>
#include <iostream>

using namespace XYZEngine;

namespace XYZRoguelike {
class DeveloperLevel : public Scene {
   public:
    void Start() override;
    void Restart() override;
    void Stop() override;
    void AddWallTheBorder();
    void CreateExit();
    void GenerateMaze();

    template<typename AIBoss> void AddBoss() {
        auto boss = std::make_shared<Boss<AIBoss>>(
            XYZEngine::Vector2Df({200.f, 200.f}), "Boss");
        if(levelExit) 
        {
            levelExit->SetIsDoorClosed(true);
        }
    }

    template<typename AIType, typename WeaponType> void AddSpawner() {
        auto enemySpawner =
            std::make_shared<NPCSpawner<Enemy<AIType, WeaponType>>>(
                XYZEngine::Vector2Df{400.f, 400.f}, 1.f, 3, true,
                "SpawnerEnemy: " + std::to_string(numSpawners));
        ++numSpawners;
    }

    template<typename AIType, typename WeaponType> void AddEnemy() {
        auto enemy = std::make_shared<Enemy<AIType, WeaponType>>(
            XYZEngine::Vector2Df({350.f, 350.f}), "Enemy");
    }

    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<std::unique_ptr<Floor>> floors;

   private:
    std::unique_ptr<LevelExit> levelExit = nullptr;
    std::unique_ptr<Player> player = nullptr;
    std::unique_ptr<SoundPlayer> backgroundMusic = nullptr;
    int width = GameSettings::Instance()->MAP_WIDTH;
    int height = GameSettings::Instance()->MAP_HEIGHT;
    float sizeBlock = GameSettings::Instance()->BLOCK_SIZE;
    int x_Offset = 0;
    int y_Offset = 0;
    int numSpawners = 0;
};
}  // namespace XYZRoguelike