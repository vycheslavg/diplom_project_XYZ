#pragma once
#include "Component.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "InitializeNPCSpawnerComponent.h"
#include "Logger.h"
#include "TransformComponent.h"

#include <functional>

namespace XYZRoguelike {
template<typename T> class SpawnerComponent : public XYZEngine::Component {
   public:
    SpawnerComponent(XYZEngine::GameObject* gameObject)
        : Component(gameObject) {
        transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
        auto initializeSpawner =
            gameObject->GetComponent<InitializeNPCSpawnerComponent>();
        try {
            if (!initializeSpawner) {
                throw std::invalid_argument(
                    "Component: InitializeNPCSpawnerComponent not found\n");
            }
        } catch (const std::invalid_argument& e) {
            LOG_WARN(e.what());
        }

        timeSpawn = initializeSpawner->GetTimeSpawn();
        maxSimultaneouslyExistingObject = initializeSpawner->GetMaxSpawn();
        isEndless = initializeSpawner->GetIsEndless();
    }

    virtual void Update(float deltaTime) override {
        time += 1.f * deltaTime;
        switch (isEndless) {
            case 0:
                if (time >= timeSpawn && numberSimultaneouslyExistingObject <
                        maxSimultaneouslyExistingObject &&
                    XYZEngine::GameWorld::Instance()
                            ->GetNumberGameObjectsByName(name) < 1) {
                    auto NPC = std::make_shared<T>(
                        transform->GetWorldPosition(), name);
                    ++numberSimultaneouslyExistingObject;
                    time = 0.f;
                }
                break;
            case 1:
                numberSimultaneouslyExistingObject =
                    XYZEngine::GameWorld::Instance()
                        ->GetNumberGameObjectsByName(name);
                if (time >= timeSpawn && numberSimultaneouslyExistingObject <
                        maxSimultaneouslyExistingObject &&
                    XYZEngine::GameWorld::Instance()
                            ->GetNumberGameObjectsByName(name) < 1) {
                    auto NPC = std::make_shared<T>(
                        transform->GetWorldPosition(), name);
                    time = 0.f;
                }
                break;
        }
    }
    virtual void Render() override {};

   private:
    XYZEngine::TransformComponent* transform;
    float time = 0.f;
    int numberSimultaneouslyExistingObject = 0;
    float timeSpawn = 0.f;
    int maxSimultaneouslyExistingObject = 0;
    std::string name = "";
    bool isEndless = false;
};

}  // namespace XYZRoguelike