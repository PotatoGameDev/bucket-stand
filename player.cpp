#include "player.h"
#include "bullet.h"
#include <raylib.h>
#include <vector>

namespace potato_bucket {
Player::Player(float x, float y, float w, float h)
    : box{x, y, w, h}, anim("bucketman.png", 6, x, y, 48.0, 48.0),
      scale{1.0, 1.0}, velocity{0.0, 0.0} {}

void Player::update(int frameNo, std::vector<Bullet>& bullets) {
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

  // Generate bullets
  if (frameNo % (3 * 60) == 0) {
    Rectangle brec{box.x, box.y, 6.0f, 4.0f};
    float signX = (scale.x < 0.0 ? -1.0 : 1.0);
    float signY = (scale.y < 0.0 ? -1.0 : 1.0);
    Vector2 bvel{signX * 1.0f + velocity.x,
                 signY * 0.0f + velocity.y};
    bullets.emplace_back(brec, bvel);
  }

  box.x += velocity.x;
  box.y += velocity.y;
  anim.update();
}

void Player::draw() { anim.draw(Vector2{box.x, box.y}, scale); }
void Player::unload() { anim.unload(); }
} // namespace potato_bucket
