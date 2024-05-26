#include "player.h"
#include <raylib.h>

namespace potato_bucket {
Player::Player(float x, float y, float w, float h)
    : box{x, y, w, h}, anim("player-run.png", 6, x, y, 48.0, 48.0),
      scale{1.0, 1.0}, velocity{0.0, 0.0} {}

void Player::update() {
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

  box.x += velocity.x;
  box.y += velocity.y;
  anim.update();
}

void Player::draw() { anim.draw(Vector2{box.x, box.y}, scale); }
void Player::unload() { anim.unload(); }
} // namespace potato_bucket
