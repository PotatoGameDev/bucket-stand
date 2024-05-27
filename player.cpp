#include "player.h"
#include "bullet.h"
#include <raylib.h>
#include <raymath.h>
#include <vector>

namespace potato_bucket {
Player::Player(float x, float y, float w, float h, PlayerStats stats)
    : box{x, y, w, h}, anim("bucketman.png", 6, x, y, 48.0, 48.0),
      scale{1.0, 1.0}, velocity{0.0, 0.0}, currentStats{stats} {}

void Player::update(int frameNo, std::vector<Bullet> &bullets) {
  velocity.x = 0.0;
  velocity.y = 0.0;

  if (IsKeyDown(KEY_D)) {
    velocity.y = 1.0;
  }
  if (IsKeyDown(KEY_E)) {
    velocity.y = -1.0;
  }
  if (IsKeyDown(KEY_S)) {
    velocity.x = -1.0;
    scale = {-1.0, 1.0};
  }
  if (IsKeyDown(KEY_F)) {
    velocity.x = 1.0;
    scale = {1.0, 1.0};
  }

  // VIM MODE
  if (IsKeyDown(KEY_J)) {
    velocity.y = 1.0;
  }
  if (IsKeyDown(KEY_K)) {
    velocity.y = -1.0;
  }
  if (IsKeyDown(KEY_H)) {
    velocity.x = -1.0;
    scale = {-1.0, 1.0};
  }
  if (IsKeyDown(KEY_L)) {
    velocity.x = 1.0;
    scale = {1.0, 1.0};
  }

  velocity = Vector2Scale(Vector2Normalize(velocity), currentStats.maxSpeed);

  if (!Vector2Equals(velocity, Vector2Zero())) {
      lastNonZeroVelocity = velocity;
  }

  // Generate bullets
  if (frameNo % (currentStats.shootEveryFrames) == 0) {
    Rectangle brec{box.x, box.y, 6.0f, 4.0f};
    float signX = (scale.x < 0.0 ? -1.0 : 1.0);
    float signY = (scale.y < 0.0 ? -1.0 : 1.0);

    float bulletSpeed = 1.0f;
    Vector2 bvel = Vector2Add(
        velocity, Vector2Scale(Vector2Normalize(lastNonZeroVelocity), bulletSpeed));
    bullets.emplace_back(brec, bvel, 5);
  }

  box.x += velocity.x;
  box.y += velocity.y;
  anim.update();
}

void Player::draw() { anim.draw(Vector2{box.x, box.y}, scale); }
void Player::unload() { anim.unload(); }
} // namespace potato_bucket
