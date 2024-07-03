#include "bullet.h"
#include <raylib.h>

#include <iostream>
#include <raymath.h>

namespace potato_bucket {
Bullet::Bullet(float x, float y, float w, float h, Vector2 _velocity,
               int maxLife, bool playerBullet)
    : Bullet(Rectangle{x, y, w, h}, _velocity, maxLife) {}

Bullet::Bullet(Rectangle r, Vector2 _velocity, int maxLife, bool playerBullet)
    : box{r}, velocity{_velocity}, timeToLive{maxLife * 60}, playerBullet{playerBullet} {}

void Bullet::update() {
  box.x += velocity.x;
  box.y += velocity.y;
  timeToLive--;
}

void Bullet::draw() const {
  DrawRectangleV(Vector2{box.x, box.y}, Vector2{box.width, box.height}, WHITE);
}

bool Bullet::dead() const { return timeToLive <= 0; }

void Bullet::bounce(Vector2 otherVelocity) {
  velocity = Vector2Add(otherVelocity, Vector2Invert(velocity));
}

} // namespace potato_bucket
