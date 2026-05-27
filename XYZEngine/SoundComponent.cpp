#include "pch.h"

#include "SoundComponent.h"

XYZEngine::SoundComponent::SoundComponent(GameObject* gameObject)
    : Component(gameObject) {
    playSound = new sf::Sound();
}

XYZEngine::SoundComponent::~SoundComponent() { delete playSound; }

void XYZEngine::SoundComponent::Update(float deltaTime) {}

void XYZEngine::SoundComponent::Render() {}

void XYZEngine::SoundComponent::SetSound(const sf::SoundBuffer& sound) {
    playSound->setBuffer(sound);
}

void XYZEngine::SoundComponent::SetLoop(bool loop) { playSound->setLoop(loop); }

void XYZEngine::SoundComponent::SetVolume(float volume) {}

void XYZEngine::SoundComponent::Play() {
    if (playSound->getStatus() != playSound->Playing) {
        playSound->play();
    }
}

void XYZEngine::SoundComponent::Stop() { playSound->stop(); }

void XYZEngine::SoundComponent::Pause() { playSound->pause(); }
