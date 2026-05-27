#pragma once
#include "GameObject.h"
#include "Component.h"

namespace XYZEngine
{
class ProjectileMovementComponent : public Component {
   public:
    ProjectileMovementComponent(GameObject* gameObject);
	
    void Update(float deltaTime) override;
    void Render() override;
    void SetSpeed(float newSpeed);
    void SetDirection(Vector2Df newDirection);
    void SetLifeTime(float newLifeTime);
    float GetLifeTime();

    private:
    TransformComponent* transform = nullptr;
     float speed = 0.f;
     float lifeTime = 15.f;
    Vector2Df direction = {0.f, 0.f};
};
}  // namespace XYZEngine