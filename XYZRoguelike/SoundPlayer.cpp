#include "SoundPlayer.h"

SoundPlayer::SoundPlayer(const std::string& soundName) {
    auto gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject(
        "Sound: " + soundName);
    auto music = gameObject->AddComponent<XYZEngine::SoundComponent>();
    music->SetSound(
        *XYZEngine::ResourceSystem::Instance()->GetSound(soundName));
    music->SetLoop(true);
    music->Play();
}
