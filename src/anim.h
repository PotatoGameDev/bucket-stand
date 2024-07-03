#ifndef POTATO_BUCKET_ANIM_H
#define POTATO_BUCKET_ANIM_H

#include "raylib.h"
#include <memory>
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
  std::shared_ptr<Texture2D> texture;

public:

  int width {};
  int height {};

  std::string textureFile;

  Anim(std::string, int);

  ~Anim() = default;
  Anim(Anim &&) noexcept;
  Anim &operator=(Anim &&) noexcept;

  void update();
  void draw(Vector2, Rectangle, Vector2 = {1.0, 1.0});
  std::string id();
};

} // namespace potato_bucket

#endif
