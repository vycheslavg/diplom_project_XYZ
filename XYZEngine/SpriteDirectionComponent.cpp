#include "pch.h"

#include "SpriteDirectionComponent.h"

XYZEngine::SpriteDirectionComponent::SpriteDirectionComponent(
    GameObject* gameObject)
    : Component(gameObject) {
    input = gameObject->GetComponent<InputComponent>();
    spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
}

void XYZEngine::SpriteDirectionComponent::Update(float deltaTime) {
    if (input->GetHorizontalAxis() < 0) {
        spriteRenderer->FlipX(false);

        spriteRenderer->FlipY(true);
    }
    if (input->GetHorizontalAxis() > 0) {
        spriteRenderer->FlipX(false);
        spriteRenderer->FlipY(false);
    }
    if (input->GetVerticalAxis() < 0) {
        spriteRenderer->FlipX(false);
        spriteRenderer->FlipY(false);
    }
    if (input->GetVerticalAxis() > 0) {
        spriteRenderer->FlipX(false);
        spriteRenderer->FlipY(true);
    }
}

void XYZEngine::SpriteDirectionComponent::Render() {}
