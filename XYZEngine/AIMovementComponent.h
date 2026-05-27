#pragma once
#include "GameObject.h"
namespace XYZEngine {
class AIMovementComponent : public Component {
   public:
    AIMovementComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    virtual void SetSpeed(float newSpeed);
    virtual void SetTarget(GameObject* gameObject);
    virtual void ClearTarget();
    virtual GameObject* GetTarget();
    virtual float GetSpeed() const;
    virtual float GetAccelerationSquared() const;

   protected:
    TransformComponent* transformSelf = nullptr;
    XYZEngine::GameObject* objectTarget = nullptr;

    float speed = 20.f;
    float viewingRadius = 300.f;
    Vector2Df previousPosition = {0, 0};
    Vector2Df acceleration = {0, 0};
};

}  // namespace XYZEngine