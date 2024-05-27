#ifndef POTATO_BUCKET_PLAYER_H
#define POTATO_BUCKET_PLAYER_H

#include "bullet.h"
#include "anim.h"
#include <raylib.h>
#include <raymath.h>
#include <vector>

namespace potato_bucket {


struct PlayerStats {
  float maxSpeed {1.0f};
  int shootEveryFrames {3};
};

class Player {
private:
  Anim anim;
  Vector2 lastNonZeroVelocity = Vector2{ 1.0, 0.0};

public:
  Vector2 scale;
  Rectangle box;
  Vector2 velocity;
  PlayerStats currentStats;

  Player(float, float, float, float, PlayerStats = {});

  void update(int, std::vector<Bullet>&);
  void draw();
};

} // namespace potato_bucket

#endif
