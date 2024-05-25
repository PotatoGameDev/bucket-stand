#ifndef POTATO_BUCKET_PLAYER_H
#define POTATO_BUCKET_PLAYER_H

#include "raylib.h"
#include <vector>

namespace potato_bucket {

class Player {
private:
public:
  Rectangle box;

  Player(float, float, float, float);

  void update();
  void draw();
};

} // namespace potato_bucket

#endif
