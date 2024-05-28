#ifndef POTATO_BUCKET_WORLD_H
#define POTATO_BUCKET_WORLD_H

#include "bullet.h"
#include "camera.h"
#include "enemy.h"
#include "object.h"
#include "player.h"
#include "raylib.h"
#include <cwctype>
#include <vector>

namespace potato_bucket {

enum class WorldFlow { None, Win, Lose };

struct WorldSettings {};

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

  World(unsigned int, WorldSettings = {});

  WorldFlow update();
  void draw();
};

} // namespace potato_bucket

#endif
