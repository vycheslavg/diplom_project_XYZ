#include "DeveloperLevel.h"

#include "AICreeper.h"
#include "Explosion.h"
#include "MazeGenerator.h"
#include "NPCSpawner.h"
#include "Logger.h"
#include "Sword.h"

using namespace XYZEngine;

namespace XYZRoguelike {
void DeveloperLevel::Start() {

    if(player == nullptr) {
        player = std::make_unique<Player>(std::forward<XYZEngine::Vector2Df>(
            {(x_Offset + width) / 2 * 64.f, (y_Offset + height) / 2 * 64.f}));
    }
    if(backgroundMusic == nullptr){
        backgroundMusic = std::make_unique<SoundPlayer>("BackgroundMusic");
    }

    LOG_INFO("SPAWN LEVEL");
}
void DeveloperLevel::Restart() {
    Stop();
    Start();
}
void DeveloperLevel::Stop() { 
    if (levelExit != nullptr){
        XYZEngine::GameWorld::Instance()->DestroyGameObject(
            levelExit->GetGameObject());
    }
    if(player != nullptr){
        player->GetGameObject()
            ->GetComponent<TransformComponent>()
            ->SetWorldPosition({(x_Offset + width) / 2 * 64.f,
                                (y_Offset + height) / 2 * 64.f});
    }
    for (auto it = walls.begin(); it != walls.end(); ++it) {
        XYZEngine::GameWorld::Instance()->DestroyGameObject(
            it->get()->transform->GetGameObject());
    }
    walls.clear();
    
    while (true) {
        std::vector<XYZEngine::GameObject*> aiEnemy =
            XYZEngine::GameWorld::Instance()->GetGameObjectsByComponent<AIMovementComponent>();
        if(!aiEnemy.empty()) 
        {
            for (auto it = aiEnemy.begin(); it != aiEnemy.end(); ++it) 
            {
                XYZEngine::GameWorld::Instance()->DestroyGameObject(*it);
            }
            break;
        } 
        else 
        {
            break;
        }
    }

    
    while (true) {
        std::vector<XYZEngine::GameObject*> spawnerEnemy =
            XYZEngine::GameWorld::Instance()
                ->GetGameObjectsByComponent<InitializeNPCSpawnerComponent>();
        if (!spawnerEnemy.empty()) {
            for (auto it = spawnerEnemy.begin(); it != spawnerEnemy.end();
                 ++it) {
                XYZEngine::GameWorld::Instance()->DestroyGameObject(*it);
            }
            break;
        } else {
            break;
        }
    }
}

void DeveloperLevel::CreateExit() {
    int side = std::rand() % 4;
    int exitX, exitY;

    switch (side) {
        case 0:                                     // Top screen (y = 0)
            exitX = std::rand() % (width - 1) + 1;  // not angel
            exitY = 0;
            break;
        case 1:  // Right screen (x = width - 1)
            exitX = width;
            exitY = std::rand() % (height - 1) + 1;
            break;
        case 2:  // Down screen (y = height - 1)
            exitX = std::rand() % (width - 1) + 1;
            exitY = height;
            break;
        case 3:  // Left screen (x = 0)
            exitX = 0;
            exitY = std::rand() % (height - 1) + 1;
            break;
    }

    levelExit = std::make_unique<LevelExit>(
        XYZEngine::Vector2Df{exitX * 64.f, exitY * 64.f});

    for (auto it = walls.begin(); it != walls.end(); ++it) {
        auto& wall = *it;  // unique_ptr<Wall>
        if (wall.get()->transform->GetWorldPosition().x == exitX * 64.f &&
            wall.get()->transform->GetWorldPosition().y == exitY * 64.f) {
            XYZEngine::GameWorld::Instance()->DestroyGameObject(
                wall.get()->transform->GetGameObject());
            it = walls.erase(it);
        }
    }
}

void DeveloperLevel::AddWallTheBorder() {
    bool floorEmpty = floors.empty();
    for (int y = 0; y < height + 1; y++) {
        for (int x = 0; x < width + 1; x++) {
            // if not wall place
            if (x != 0 && x != width && y != 0 && y != height && floorEmpty) {
                floors.push_back(std::make_unique<Floor>(
                    std::forward<XYZEngine::Vector2Df>(
                        {x_Offset + x * 64.f, y_Offset + y * 64.f}),
                    std::forward<int>(0)));
            }

            // Left-bottom angle screen
            if (x == 0 && y == 0) {
                walls.push_back(std::make_unique<Wall>(
                    std::forward<XYZEngine::Vector2Df>(
                        {x_Offset + x * 64.f, y_Offset + y * 64.f}),
                    std::forward<int>(25)));
            }

            // Right-bottom angle screen
            if (x == width && y == 0) {
                walls.push_back(std::make_unique<Wall>(
                    std::forward<XYZEngine::Vector2Df>(
                        {x_Offset + x * 64.f, y_Offset + y * 64.f}),
                    std::forward<int>(27)));
            }

            // Left-top angle screen
            if (x == 0 && y == height) {
                walls.push_back(std::make_unique<Wall>(
                    std::forward<XYZEngine::Vector2Df>(
                        {x_Offset + x * 64.f, y_Offset + y * 64.f}),
                    std::forward<int>(1)));
            }

            // Right-top angle screen
            if (x == width && y == height) {
                walls.push_back(std::make_unique<Wall>(
                    std::forward<XYZEngine::Vector2Df>(
                        {x_Offset + x * 64.f, y_Offset + y * 64.f}),
                    std::forward<int>(3)));
            }

            // Left screen
            if (x == 0 && y != height && y != 0) {
                if (floorEmpty) {
                    floors.push_back(std::make_unique<Floor>(
                        std::forward<XYZEngine::Vector2Df>(
                            {x_Offset + x * 64.f, y_Offset + y * 64.f}),
                        std::forward<int>(18)));
                }
                walls.push_back(std::make_unique<Wall>(
                    std::forward<XYZEngine::Vector2Df>(
                        {x_Offset + x * 64.f, y_Offset + y * 64.f}),
                    std::forward<int>(12)));
            }

            // Right screen
            if (x == width && y != height && y != 0) {
                if (floorEmpty) {
                floors.push_back(std::make_unique<Floor>(
                    std::forward<XYZEngine::Vector2Df>(
                        {x_Offset + x * 64.f, y_Offset + y * 64.f}),
                    std::forward<int>(19)));
                }
                walls.push_back(std::make_unique<Wall>(
                    std::forward<XYZEngine::Vector2Df>(
                        {x_Offset + x * 64.f, y_Offset + y * 64.f}),
                    std::forward<int>(12)));
            }

            // Bottom screen
            if (y == 0 && x != width && x != 0) {
                walls.push_back(std::make_unique<Wall>(
                    std::forward<XYZEngine::Vector2Df>(
                        {x_Offset + x * 64.f, y_Offset + y * 64.f}),
                    std::forward<int>(38)));
            }

            // Top screen
            if (y == height && x != width && x != 0) {
                walls.push_back(std::make_unique<Wall>(
                    std::forward<XYZEngine::Vector2Df>(
                        {x_Offset + x * 64.f, y_Offset + y * 64.f}),
                    std::forward<int>(38)));
            }
        }
    }
}
    void DeveloperLevel::GenerateMaze() {
    int generatWidth = width - 1;
    int generatHeight = height - 1;
    int generatOffsetWidth = 1;
    int generatOffsetHeight = 1;
    MazeGenerator mazeGenerator(generatWidth, generatHeight, this,
                                generatOffsetWidth, generatOffsetHeight);
    mazeGenerator.Generate();
}
}  // namespace XYZRoguelike