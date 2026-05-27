#pragma once
#include <Component.h>
#include <string>
namespace XYZRoguelike {
class InitializeNPCSpawnerComponent : public XYZEngine::Component {
   public:
    InitializeNPCSpawnerComponent(XYZEngine::GameObject* gameObject)
        : XYZEngine::Component(gameObject) {};
    void Update(float deltaTime) override {};
    void Render() override {};

    void Initialize(float& spawnInterval, float& maxSpawn, bool& isEndlessSpawn,
                    std::string uniqueNameSpawnObject) {
        timeSpawn = spawnInterval;
        maxSimultaneouslyExistingObject = maxSpawn;
        isEndless = isEndlessSpawn;
        name = uniqueNameSpawnObject;
    }

    float GetTimeSpawn() { return timeSpawn; }

    std::string GetName() { return name; }

    int GetMaxSpawn() { return maxSimultaneouslyExistingObject; }

    bool GetIsEndless() { return isEndless; }

   private:
    float timeSpawn = 0.f;
    int maxSimultaneouslyExistingObject = 0;
    std::string name = "";
    bool isEndless = false;
};
}  // namespace XYZRoguelike
