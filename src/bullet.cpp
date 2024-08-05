#include "bullet.h"
#include <raylib.h>

#include <raymath.h>

namespace potato_bucket {
Bullet::Bullet(float x, float y, Vector2 velocity, int maxLife, int size,
               bool playerBullet)
    : Bullet(Vector2{x, y}, velocity, maxLife, size) {}

Bullet::Bullet(Vector2 position, Vector2 _velocity, int maxLife, int size,
               bool playerBullet)
    : position{position}, velocity{_velocity}, timeToLive{maxLife * 60},
      playerBullet{playerBullet},
      box{position.x - size / 2.0f, position.y - size / 2.0f,
          static_cast<float>(size), static_cast<float>(size)} {}

void Bullet::update() {
  position.x += velocity.x;
  position.y += velocity.y;
  timeToLive--;
}

void Bullet::draw() const {
  DrawRectangleV(position,
                 Vector2{static_cast<float>(size), static_cast<float>(size)},
                 WHITE);
}

bool Bullet::dead() const { return timeToLive <= 0; }

void Bullet::bounce(Vector2 otherVelocity) {
  velocity = Vector2Add(otherVelocity, Vector2Invert(velocity));
}

} // namespace potato_bucket
