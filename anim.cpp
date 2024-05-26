#include "anim.h"
#include "texture_cache.h"
#include <raylib.h>
#include <string>
#include <iostream>

namespace potato_bucket {
Anim::Anim(std::string file, int _frames, float x, float y, float w, float h)
    : Anim(file, _frames, Rectangle{x, y, w, h}) {}

Anim::Anim(std::string filename, int _frames, Rectangle r)
    : box{r}, frames{_frames}, frameRect{0.0, 0.0, r.width, r.height},
      texture(TextureCache::Instance().load(filename)) {

          std::cout << "Initialized anim with file: " << filename << std::endl;
}

void Anim::unload() {} 

void Anim::update() {
  framesCounter++;

  if (framesCounter >= (60 / framesSpeed)) {
    framesCounter = 0;
    currentFrame++;

    if (currentFrame > frames) {
      currentFrame = 0;
    }

    frameRect.x = (float)currentFrame * (float)box.width;
  }
}

void Anim::draw(Vector2 where, Vector2 scaled) {
  Rectangle from{frameRect.x, frameRect.y, frameRect.width * scaled.x,
                 frameRect.height * scaled.y};
  DrawTextureRec(texture, from, where, WHITE);
}
} // namespace potato_bucket
