#pragma once
#include "DeveloperLevel.h"

namespace XYZRoguelike {
class LevelManager {
   public:
    static LevelManager* Instance();
    void LoadRandomLevels();
   private:
    LevelManager() {}
    ~LevelManager() {}

    LevelManager(LevelManager const&) = delete;
    LevelManager& operator=(LevelManager const&) = delete;
    std::unique_ptr<DeveloperLevel> level;
    int currentLevel = 0;
};
}  // namespace XYZRoguelike
