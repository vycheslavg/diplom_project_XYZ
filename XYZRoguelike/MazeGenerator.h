#include "DeveloperLevel.h"

#include <stack>
#include <vector>

namespace XYZRoguelike {
class MazeGenerator {
   public:
    MazeGenerator(int width, int height, DeveloperLevel* level, float offsetX,
                  float offsetY);
    void Generate();

   private:
    int width, height;
    float offsetX, offsetY;
    DeveloperLevel* level;
    std::vector<std::vector<bool>> grid;

    std::vector<std::pair<int, int>> GetAvailableDirections(int x, int y);
    void RemoveWall(int x1, int y1, int x2, int y2);
};
}  // namespace XYZRoguelike