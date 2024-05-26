#ifndef POTATO_BUCKET_PLAYER_H
#define POTATO_BUCKET_PLAYER_H

#include "bullet.h"
#include "anim.h"
#include "raylib.h"
#include <vector>

namespace potato_bucket {

class Player {
private:
  Anim anim;

public:
  Vector2 scale;
  Rectangle box;
  Vector2 velocity;

  Player(float, float, float, float);

  void update(int, std::vector<Bullet>&);
  void draw();
  void unload();
};

} // namespace potato_bucket

#endif
