#include "pch.h"
#include "ProjectileMovementComponent.h"

namespace XYZEngine {

	ProjectileMovementComponent::ProjectileMovementComponent(GameObject* gameObject)
    : Component(gameObject) {
    transform = gameObject->GetComponent<TransformComponent>();

}

void ProjectileMovementComponent::Update(float deltaTime) 
{
    transform->MoveBy(speed * deltaTime *
                          XYZEngine::Vector2Df{direction.x, direction.y});
    if (lifeTime >= 0.f)
    {
    lifeTime -= 1.f * deltaTime;
    }
}

void ProjectileMovementComponent::Render() {}

void ProjectileMovementComponent::SetSpeed(float newSpeed) { speed = newSpeed; }

void ProjectileMovementComponent::SetDirection(Vector2Df newDirection) { direction = newDirection; }

void ProjectileMovementComponent::SetLifeTime(float newLifeTime) { lifeTime = newLifeTime; }

float ProjectileMovementComponent::GetLifeTime() { return lifeTime; }

}  // namespace XYZEngine