#ifndef POTATO_BUCKET_PLAYER_H
#define POTATO_BUCKET_PLAYER_H

#include "anim.h"
#include "raylib.h"
#include <vector>

namespace potato_bucket {

class Player {
private:
    Anim anim;
    Vector2 scale;

public:
  Rectangle box;

  Player(float, float, float, float);

  void update();
  void draw();
  void unload();
};

} // namespace potato_bucket

#endif
