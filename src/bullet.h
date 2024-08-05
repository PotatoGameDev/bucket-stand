#ifndef POTATO_BUCKET_BULLET_H
#define POTATO_BUCKET_BULLET_H

#include "raylib.h"

namespace potato_bucket {

class Bullet {
private:
  int timeToLive{};

public:
  Vector2 position;
  Vector2 velocity;

  int size;
  Rectangle box;
  bool playerBullet{false};

  Bullet(float, float, Vector2, int = 1, int = 6, bool = false);
  Bullet(Vector2, Vector2, int = 1, int = 6, bool = false);

  void update();
  void draw() const;
  bool dead() const;

  void bounce(Vector2);
};

} // namespace potato_bucket

#endif
