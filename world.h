#ifndef POTATO_BUCKET_WORLD_H
#define POTATO_BUCKET_WORLD_H

#include "bullet.h"
#include "camera.h"
#include "player.h"
#include "object.h"
#include "raylib.h"
#include <vector>

namespace potato_bucket {

class World {
private:
  Texture2D backgnd;
  std::vector<Object> objects;
  std::vector<Bullet> bullets;
  float secondsSinceLastBullet {};

public:
  Player player;
  Camera2D camera;

  World();

  void update();
  void draw();
  void unload();
};

} // namespace potato_bucket

#endif
