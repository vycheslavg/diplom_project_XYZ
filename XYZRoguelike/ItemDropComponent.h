#pragma once
#include "Component.h"
#include "GameObject.h"
#include "GameWorld.h"
namespace XYZRoguelike {
class ItemDropComponent : public XYZEngine::Component {
   public:
    ItemDropComponent(XYZEngine::GameObject* gameObject);
    void Drop();
    void Update(float deltaTime) override {};
    void Render() override {};
   private:
};
}  // namespace XYZRoguelike