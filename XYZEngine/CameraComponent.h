#pragma once

#include "TransformComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace XYZEngine {
class CameraComponent : public Component {
   public:
    CameraComponent(GameObject* gameObject);
    ~CameraComponent();

    void Update(float deltaTime) override;
    void Render() override;

    void SetWindow(sf::RenderWindow* newWindow);
    void ZoomBy(float newZoom);
    void SetTurnTracking(bool isTracking);
    void SetBaseResolution(int width, int height);

   private:
    bool isTurnTracking = true;
    TransformComponent* transform;
    sf::RenderWindow* window;
    sf::View* view;
};
}  // namespace XYZEngine