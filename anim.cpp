#include "anim.h"
#include "texture_cache.h"
#include <ios>
#include <iostream>
#include <raylib.h>
#include <string>

namespace potato_bucket {
Anim::Anim(std::string filename, int frames)
    : frames{frames}, frameRect{}, textureFile(filename),
      texture{TextureCache::Instance().load(filename)} {
  width = texture->width / frames;
  height = texture->height;
  frameRect = {0.0, 0.0, static_cast<float>(width), static_cast<float>(height)};
  std::cout << "Initialized anim with file: " << filename << " texture id: " << texture->id << std::endl;
}

// Move constructor
Anim::Anim(Anim &&other) noexcept
    : framesCounter(other.framesCounter), currentFrame(other.currentFrame),
      framesSpeed(other.framesSpeed), frames(other.frames),
      frameRect(other.frameRect), texture(other.texture),
      textureFile(other.textureFile), width(other.width), height(other.height) {

  std::cout << "Move constructor : " << textureFile << "-" << texture->id << " = " <<  other.textureFile << "-" << other.texture->id <<  std::endl;
}

// Move assignment operator
Anim &Anim::operator=(Anim &&other) noexcept {
  if (this != &other) {
    std::cout << "Move operator: " << textureFile << "-" << texture->id << " = " <<  other.textureFile << "-" << other.texture->id <<  std::endl;
    framesCounter = other.framesCounter;
    currentFrame = other.currentFrame;
    framesSpeed = other.framesSpeed;
    frames = other.frames;
    frameRect = other.frameRect;
    texture = other.texture; // TODO: HERE IS THE BUG!!!!!!!!!!!
    textureFile = other.textureFile;
    width = other.width;
    height = other.height;
    std::cout << "After move operator: " << textureFile << "-" << texture->id << "-" << texture->width << " = " <<  other.textureFile << "-" << other.texture->id << "-" << other.texture->width <<  std::endl;
  }
  return *this;
}

void Anim::update() {
  framesCounter++;

  if (framesCounter >= (60 / framesSpeed)) {
    framesCounter = 0;
    currentFrame++;

    if (currentFrame > frames) {
      currentFrame = 0;
    }

    frameRect.x = (float)currentFrame * (float)width;
  }
}

void Anim::draw(Vector2 where, Rectangle dest, Vector2 scaled) {
  Rectangle from{frameRect.x, frameRect.y, frameRect.width * scaled.x,
                 frameRect.height * scaled.y};
  DrawTexturePro(*texture, from, dest, {0.0, 0.0}, 0.0f, WHITE);
}

std::string Anim::id() {
  return std::to_string(texture->id) + "-" + textureFile;
}

} // namespace potato_bucket
