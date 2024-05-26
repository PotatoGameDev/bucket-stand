#ifndef POTATO_BUCKET_ANIM_H
#define POTATO_BUCKET_ANIM_H

#include "raylib.h"
#include <string>
#include <vector>

namespace potato_bucket {

class Anim {
private:
  int framesCounter = 0;
  int currentFrame = 0;
  int framesSpeed = 8;
  int frames;
  Rectangle frameRect;
  Rectangle box;
  Texture2D& texture;


public:
  Anim(std::string, int, float, float, float, float);
  Anim(std::string, int, Rectangle);

  void update();
  void draw(Vector2, Vector2 = {1.0, 1.0});
  void unload();
};

} // namespace potato_bucket

#endif
