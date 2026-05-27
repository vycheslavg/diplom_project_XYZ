#pragma once

#include "Component.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace XYZEngine {
class SoundComponent : public Component {
   public:
    SoundComponent(GameObject* gameObject);
    ~SoundComponent();

    void Play();
    void Stop();
    void Pause();
    void Update(float deltaTime) override;
    void Render() override;
    void SetSound(const sf::SoundBuffer& sound);
    void SetLoop(bool loop);
    void SetVolume(float volume);

   private:
    sf::Sound* playSound;
};
}  // namespace XYZEngine
