#ifndef POTATO_BUCKET_BULLET_H
#define POTATO_BUCKET_BULLET_H

#include "anim.h"
#include "raylib.h"
#include <string>
#include <vector>

namespace potato_bucket {

class Bullet {
private:
public:
  Rectangle box;
  Vector2 velocity;

  Bullet(float, float, float, float, Vector2);
  Bullet(Rectangle, Vector2);

  void update();
  void draw();
  void unload();

};

} // namespace potato_bucket

#endif
