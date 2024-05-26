#ifndef POTATO_BUCKET_BULLET_H
#define POTATO_BUCKET_BULLET_H

#include "anim.h"
#include "raylib.h"
#include <string>
#include <vector>

namespace potato_bucket {

class Bullet {
private:
    int timeToLive {};
public:
  Rectangle box;
  Vector2 velocity;

  Bullet(float, float, float, float, Vector2, int = 1);
  Bullet(Rectangle, Vector2, int = 1);

  void update();
  void draw();
  bool dead();

};

} // namespace potato_bucket

#endif
