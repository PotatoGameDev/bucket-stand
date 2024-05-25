#ifndef POTATO_BUCKET_WORLD_H
#define POTATO_BUCKET_WORLD_H

#include "camera.h"
#include "player.h"
#include "object.h"
#include "raylib.h"
#include <vector>

namespace potato_bucket {

class World {
private:
  Texture2D backgnd;
public:
  Player player;
  Camera2D camera;
  std::vector<Object> objects;

  World();

  void update();
  void draw();
  void unload();
};

} // namespace potato_bucket

#endif
