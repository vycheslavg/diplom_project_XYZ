#include "ControllerInputComponent.h"

#include "GameObject.h"
namespace XYZRoguelike {
ControllerInputComponent::ControllerInputComponent(
    XYZEngine::GameObject* gameObject)
    : Component(gameObject) {
    input = gameObject->GetComponent<XYZEngine::InputComponent>();
    attackComponent = gameObject->GetComponent<AttackComponent>();
}
void ControllerInputComponent::Update(float deltaTime) {
    if (input->GetSpaceBarPressed()) {
        attackComponent->Attack();
    }
}
void ControllerInputComponent::Render() {}
}  // namespace XYZRoguelike