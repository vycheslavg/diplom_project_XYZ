#pragma once

#include "GameObject.h"
#include "PhysicsSystem.h"

namespace XYZEngine {
class GameWorld {
   public:
    static GameWorld* Instance();

    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);
    void Render();
    void LateUpdate();

    GameObject* CreateGameObject();
    GameObject* CreateGameObject(std::string name);
    GameObject* GetGameObjectByName(std::string name);
    int GetNumberGameObjectsByName(std::string name);
    template<typename Component> 
    std::vector<GameObject*> GetGameObjectsByComponent() {

        std::vector<GameObject*> result;
        for (const auto& gameObject : gameObjects) {
            if (gameObject->GetComponent<Component>() != nullptr) {
                result.push_back(gameObject);
            }
        }
        return result;
    }
    void DestroyGameObject(GameObject* gameObject);
    void Clear();

    void Print() const;

   private:
    GameWorld() {}
    ~GameWorld() {}

    GameWorld(GameWorld const&) = delete;
    GameWorld& operator=(GameWorld const&) = delete;

    float fixedCounter = 0.f;

    std::vector<GameObject*> gameObjects = {};
    std::vector<GameObject*> markedToDestroyGameObjects = {};

    void DestroyGameObjectImmediate(GameObject* gameObject);
};
}  // namespace XYZEngine