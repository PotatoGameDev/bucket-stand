#ifndef POTATO_BUCKET_WORLD_H
#define POTATO_BUCKET_WORLD_H

#include "bullet.h"
#include "camera.h"
#include "enemy.h"
#include "object.h"
#include "player.h"
#include "raylib.h"
#include <cwctype>
#include <string>
#include <vector>

namespace potato_bucket {

enum class WorldFlow { None, Win, Lose };

struct WorldSettings {
    int winCondition{1};
    std::string location;
    std::string nextLocation;

    WorldSettings() = default;
    WorldSettings(int, std::string, std::string);
};

struct WorldResult {
    int killed{};
    bool win{};
    std::string location;
    std::string nextLocation;
    bool intro {false};
};

class World {
private:
  Texture2D backgnd;
  std::vector<Object> objects{};
  std::vector<Bullet> bullets{};
  std::vector<Enemy> enemies{};
  int frameNo{};
  WorldSettings settings;

public:
  Player player;
  Camera2D camera;

  World();
  World(unsigned int, WorldSettings settings = {});

  WorldFlow update();
  void draw();
  WorldResult result();
};

} // namespace potato_bucket

#endif
