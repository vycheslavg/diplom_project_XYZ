#include "ItemDropComponent.h"
#include "InventoryComponent.h"
namespace XYZRoguelike
{
ItemDropComponent::ItemDropComponent(XYZEngine::GameObject* gameObject)
    : Component(gameObject) {}
void ItemDropComponent::Drop() 
{
    auto target = XYZEngine::GameWorld::Instance()
        ->GetGameObjectsByComponent<InventoryComponent>();
    if(!target.empty())
    {
        target.back()->GetComponent<InventoryComponent>()->AddKey();
    }
}
}