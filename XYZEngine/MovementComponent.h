#pragma once
#include "GameObject.h"
#include "InputComponent.h"

namespace XYZEngine {
class MovementComponent : public Component {
   public:
    MovementComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void SetSpeed(float newSpeed);
    void SetDirectionalRotation(bool newDirectionalRotation);
    float GetSpeed() const;
    float GetAccelerationSquared() const;

   private:
    InputComponent* input;
    TransformComponent* transform;

    float lastHorizontalAxis = 0.f, lastVerticalAxis = 0.f;
    float speed = 0;
    float angle = 0.f;
    bool directionalRotation;
    Vector2Df previousPosition = {0.f, 0.f};
    Vector2Df acceleration = {0.f, 0.f};
};
}  // namespace XYZEngine
