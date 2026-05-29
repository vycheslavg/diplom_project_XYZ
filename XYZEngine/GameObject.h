#pragma once

#include "TransformComponent.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace XYZEngine {
class TransformComponent;

class GameObject {
   public:
    GameObject();
    GameObject(std::string newName);

    ~GameObject();

    std::string GetName() const;
    void Print(int depth = 0) const;

    void Update(float deltaTime);
    void Render();

    template<typename T> T* AddComponent() {
        static_assert(std::is_base_of<Component, T>::value,
                      "T must be derived from Component");

        if constexpr (std::is_same<T, TransformComponent>::value) {
            if (GetComponent<TransformComponent>() != nullptr) {
                throw std::logic_error(
                    "Can't add another TransformComponent to GameObject");
            }
        }

        T* newComponent = new T(this);
        assert(newComponent != nullptr && "Component allocation failed");

        components.push_back(newComponent);

        return newComponent;
    }

    void RemoveComponent(Component* component) {
        if (component == nullptr) {
            throw std::invalid_argument(
                "Attempt to remove nullptr component");
        }

        const auto iterator =
            std::find(components.begin(), components.end(), component);

        if (iterator == components.end()) {
            throw std::runtime_error(
                "Attempt to remove component that does not belong to object");
        }

        components.erase(iterator);
        delete component;
        std::cout << "Deleted component";
    }

    template<typename T> T* GetComponent() const {
        static_assert(std::is_base_of<Component, T>::value,
                      "T must be derived from Component");

        for (const auto& component : components) {
            if (auto casted = dynamic_cast<T*>(component)) {
                return casted;
            }
        }

        return nullptr;
    }

    template<typename T> T* GetComponentInChildren() const {
        T* component = GetComponent<T>();
        if (component != nullptr || children.size() == 0) {
            return component;
        }

        for (const auto& child : children) {
            T* childComponent = child->GetComponentInChildren<T>();
            if (childComponent != nullptr) {
                return childComponent;
            }
        }

        return nullptr;
    }

    template<typename T> std::vector<T*> GetComponents() const {
        std::vector<T*> result;
        for (const auto& component : components) {
            if (auto casted = dynamic_cast<T*>(component)) {
                result.push_back(casted);
            }
        }
        return result;
    }

    template<typename T> std::vector<T*> GetComponentsInChildren() const {
        std::vector<T*> result;
        for (const auto& component : GetComponents<T>()) {
            result.push_back(component);
        }

        for (const auto& child : children) {
            for (const auto& childComponent :
                 child->GetComponentsInChildren<T>()) {
                result.push_back(childComponent);
            }
        }

        return result;
    }

    void AddChild(GameObject* child);
    void RemoveChild(GameObject* child);

    friend class GameWorld;
    friend class TransformComponent;

   private:
    std::string name;

    std::vector<GameObject*> children = {};
    std::vector<Component*> components = {};
};
}  // namespace XYZEngine