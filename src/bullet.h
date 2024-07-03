#ifndef POTATO_BUCKET_BULLET_H
#define POTATO_BUCKET_BULLET_H

#include "anim.h"
#include "raylib.h"
#include <string>
#include <vector>

namespace potato_bucket {

class Bullet {
private:
  int timeToLive{};

public:
  Rectangle box;
  Vector2 velocity;
  bool playerBullet{false};

  Bullet(float, float, float, float, Vector2, int = 1, bool = false);
  Bullet(Rectangle, Vector2, int = 1, bool = false);

  void update();
  void draw() const;
  bool dead() const;

  void bounce(Vector2);
};

} // namespace potato_bucket

#endif
