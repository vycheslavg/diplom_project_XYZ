#include "InventoryComponent.h"

namespace XYZRoguelike {
InventoryComponent::InventoryComponent(XYZEngine::GameObject* gameObject)
    : Component(gameObject) {
    keys = 0;
}
void InventoryComponent::AddKey() { ++keys; }
int InventoryComponent::GetKey() { return keys; }
void InventoryComponent::UseKey() {
    if (keys > 0) {
        --keys;
    }
}
}  // namespace XYZRoguelike