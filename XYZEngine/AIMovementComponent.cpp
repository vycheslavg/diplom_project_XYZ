#include "pch.h"

#include "AIMovementComponent.h"

#include "Logger.h"

XYZEngine::AIMovementComponent::AIMovementComponent(GameObject* gameObject)
    : Component(gameObject) {
    transformSelf = gameObject->GetComponent<TransformComponent>();
}

void XYZEngine::AIMovementComponent::Update(float deltaTime) {
    Vector2Df positionAI = transformSelf->GetWorldPosition();
    auto targetTransform =
        objectTarget->GetComponent<XYZEngine::TransformComponent>();
    float distanceFromTarget =
        positionAI.CalculateDistance(targetTransform->GetWorldPosition());

    if (distanceFromTarget > viewingRadius) {
        return;
    }

    transformSelf->RotateTo(transformSelf->GetWorldPosition(),
                            targetTransform->GetWorldPosition());
    XYZEngine::Vector2Df direction =
        targetTransform->GetWorldPosition() - transformSelf->GetWorldPosition();
    direction = direction.Normalize();

    transformSelf->MoveBy(speed * deltaTime *
                          XYZEngine::Vector2Df{direction.x, direction.y});

    acceleration = transformSelf->GetWorldPosition() - previousPosition;
    previousPosition = transformSelf->GetWorldPosition();
}

void XYZEngine::AIMovementComponent::Render() {}

void XYZEngine::AIMovementComponent::SetSpeed(float newSpeed) {
    speed = newSpeed;
}

void XYZEngine::AIMovementComponent::SetTarget(GameObject* gameObject) {
    if (gameObject) {
        objectTarget = gameObject;
        LOG_INFO("Target AISwordMan: " + gameObject->GetName() + "\n");
    }
}

void XYZEngine::AIMovementComponent::ClearTarget() { objectTarget = nullptr; }

XYZEngine::GameObject* XYZEngine::AIMovementComponent::GetTarget() {
    return objectTarget;
}

float XYZEngine::AIMovementComponent::GetSpeed() const { return speed; }

float XYZEngine::AIMovementComponent::GetAccelerationSquared() const {
    return acceleration.x * acceleration.x + acceleration.y * acceleration.y;
}