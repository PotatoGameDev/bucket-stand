#ifndef POTATO_BUCKET_WORLD_H
#define POTATO_BUCKET_WORLD_H

#include "camera.h"
#include "player.h"
#include "raylib.h"
#include <vector>

namespace potato_bucket {

class World {
private:
public:
  Player player;
  Camera2D camera;

  World(float, float);

  void update();
  void draw();
};

} // namespace potato_bucket

#endif
