#include "pch.h"
#include "LevelManager.h"
#include "AICreeper.h"
#include "Explosion.h"
#include "Sword.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
namespace XYZRoguelike {

    LevelManager* LevelManager::Instance() {
        static LevelManager levels; 
            return &levels;
    }

    void XYZRoguelike::LevelManager::LoadRandomLevels() {
        ++currentLevel;
        if (level == nullptr) {
            level = std::make_unique<DeveloperLevel>();
        }
        level->Stop();
        level->AddWallTheBorder();
        level->CreateExit();
        level->Start();
        std::srand(std::time(nullptr));

              if (currentLevel % 3 != 0) {  
                 level->AddEnemy<AICreeper, Explosion>();
                  if (std::rand() % 100 < 30) 
                  {
                      level->AddSpawner<AISwordMan, Sword>();
                  }
                  level->GenerateMaze();

              } 
              else {

                 // add boss;
              } 

    }

}  // namespace XYZRoguelike