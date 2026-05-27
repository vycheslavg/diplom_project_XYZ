#pragma once
#include "Component.h"
#include "Logger.h"
namespace XYZRoguelike{
class InventoryComponent : public XYZEngine::Component 
{
   public:
    InventoryComponent(XYZEngine::GameObject* gameObject);
    void AddKey();
    int GetKey();
    void UseKey();
    void Update(float deltaTime) override {};
    void Render() override {};
   private:
    int keys = 0;
};

}  // namespace XYZRoguelike