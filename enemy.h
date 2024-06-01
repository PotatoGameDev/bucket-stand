#ifndef POTATO_BUCKET_ENEMY_H
#define POTATO_BUCKET_ENEMY_H

#include "anim.h"
#include "raylib.h"
#include "player.h"
#include <vector>

namespace potato_bucket {

class Enemy {
private:
  Anim anim;
  float maxSpeed {1.0};
  Vector2 lastNonZeroVelocity = {1.0, 0.0};

public:
  Vector2 scale {1.0, 1.0};
  Rectangle box;
  Vector2 velocity {0.0, 0.0};

  Enemy(Vector2);
  Enemy(float, float);
  
  Enemy(Enemy&&) noexcept;
  Enemy& operator=(Enemy&&) noexcept;

  void update(Player&, int, std::vector<Bullet>&);
  void draw();
};

} // namespace potato_bucket

#endif
