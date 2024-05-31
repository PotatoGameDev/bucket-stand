#include "bullet.h"
#include <raylib.h>

#include <iostream>

namespace potato_bucket {
Bullet::Bullet(float x, float y, float w, float h, Vector2 _velocity,
               int maxLife)
    : Bullet(Rectangle{x, y, w, h}, _velocity, maxLife) {}
Bullet::Bullet(Rectangle r, Vector2 _velocity, int maxLife)
    : box{r}, velocity{_velocity}, timeToLive{maxLife * 60} {}

void Bullet::update() {
  box.x += velocity.x;
  box.y += velocity.y;
  timeToLive--;
}

void Bullet::draw() {
  DrawRectangleV(Vector2{box.x, box.y}, Vector2{box.width, box.height}, WHITE);
  // DrawText(std::to_string(timeToLive/60).c_str(), box.x, box.y, 10, WHITE);
}

bool Bullet::dead() { return timeToLive <= 0; }

} // namespace potato_bucket
