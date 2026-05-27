#pragma once
#include "SoundPlayer.h"

#include <GameObject.h>
#include <GameWorld.h>
#include <ResourceSystem.h>
#include <SoundComponent.h>

class SoundPlayer {
   public:
    SoundPlayer(const std::string& soundName);

   private:
    XYZEngine::GameObject* gameObject;
};
