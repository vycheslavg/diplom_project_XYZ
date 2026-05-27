#include "pch.h"

#include "MovementComponent.h"

XYZEngine::MovementComponent::MovementComponent(GameObject* gameObject)
    : Component(gameObject) {
    input = gameObject->GetComponent<InputComponent>();
    transform = gameObject->GetComponent<TransformComponent>();

    if (input == nullptr) {
        std::cout << "Need input component for movement" << std::endl;
        gameObject->RemoveComponent(this);
    }
}

void XYZEngine::MovementComponent::Update(float deltaTime) {
    float xAxis = input->GetHorizontalAxis();
    float yAxis = input->GetVerticalAxis();
    if (input->GetVerticalAxis() != 0.f) {
        lastVerticalAxis = input->GetVerticalAxis();
        lastHorizontalAxis = 0.f;
    }
    if (input->GetHorizontalAxis() != 0.f) {
        lastHorizontalAxis = input->GetHorizontalAxis();

        lastVerticalAxis = 0.f;
    }
    angle = 0.f;
    if (lastHorizontalAxis < 0.f) {
        angle = 180.f;
    } else if (lastHorizontalAxis > 0.f) {
        angle = 0.f;
    } else if (lastVerticalAxis != 0.f) {
        angle = 90.f * lastVerticalAxis;
    }

    transform->MoveBy(speed * deltaTime * Vector2Df{xAxis, yAxis});
    if (directionalRotation) {
        transform->SetWorldRotation(angle);
    }
    acceleration = transform->GetWorldPosition() - previousPosition;
    previousPosition = transform->GetWorldPosition();
}

void XYZEngine::MovementComponent::Render() {}

void XYZEngine::MovementComponent::SetSpeed(float newSpeed) {
    speed = newSpeed;
}

void XYZEngine::MovementComponent::SetDirectionalRotation(
    bool newDirectionalRotation) {
    directionalRotation = newDirectionalRotation;
}

float XYZEngine::MovementComponent::GetSpeed() const { return speed; }

float XYZEngine::MovementComponent::GetAccelerationSquared() const {
    return acceleration.x * acceleration.x + acceleration.y * acceleration.y;
}