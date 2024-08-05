#include "player.h"
#include "audio_manager.h"
#include "bullet.h"
#include <raylib.h>
#include <raymath.h>
#include <vector>

namespace potato_bucket {
Player::Player(float x, float y, PlayerStats stats)
    : box{x, y, 0.0, 0.0}, anim("bucketman.png", 8), scale{1.0, 1.0},
      velocity{0.0, 0.0}, currentStats{stats} {
  box.width = anim.width;
  box.height = anim.height;
  currentLife = currentStats.maxLife;
}

Vector2 Player::update(int frameNo, std::vector<Bullet> &bullets,
                       Camera2D camera) {
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
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) &&
      (frameNo - lastShotFrame >= currentStats.shootEveryFrames)) {
    Vector2 bulletPosition{box.x + box.width / 2, box.y + box.height / 2};
    float signX = (scale.x < 0.0 ? -1.0 : 1.0);
    float signY = (scale.y < 0.0 ? -1.0 : 1.0);
    float bulletSpeed = 2.0f;
    Vector2 worldMousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
    Vector2 fromPlayerToMouse =
        Vector2Normalize(Vector2Subtract(worldMousePosition, {box.x, box.y}));
    Vector2 bulletVelocity =
        Vector2Add(velocity, Vector2Scale(fromPlayerToMouse, bulletSpeed));
    bullets.emplace_back(bulletPosition, bulletVelocity, 5, true);

    lastShotFrame = frameNo;

    AudioMan::Instance().play("shoot.wav");
  }

  anim.update();

  return velocity;
}

void Player::draw() { anim.draw(Vector2{box.x, box.y}, box, scale); }
} // namespace potato_bucket
