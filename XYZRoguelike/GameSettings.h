#pragma once
#include <string>

namespace XYZRoguelike {
class GameSettings {
   public:
    static GameSettings* Instance() {
        static GameSettings settings;
        return &settings;
    };
    // Game settings constants
    const unsigned int SCREEN_WIDTH = 800;
    const unsigned int SCREEN_HEIGHT = 600;

    const unsigned int MAP_WIDTH = 17;
    const unsigned int MAP_HEIGHT = 17;
    const float BLOCK_SIZE = 64.f;

    const float TIME_PER_FRAME = 1.f / 60.f;  // 60 fps

    const char* PLAYER_NAME = "Player";

    const std::string GAME_NAME = "Roguelike";
   private:
    GameSettings() {}
    ~GameSettings() {}
    GameSettings(GameSettings const&) = delete;
    GameSettings& operator=(GameSettings const&) = delete;
};
}  // namespace XYZRoguelike
