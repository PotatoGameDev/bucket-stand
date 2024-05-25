#include "player.h"
#include <raylib.h>

namespace potato_bucket {
Player::Player(float x, float y, float w, float h)
    : box{x, y, w, h}, anim("player-run.png", 6, x, y, 48.0, 48.0), scale {1.0, 1.0} {}

void Player::update() {
  if (IsKeyDown(KEY_UP)) {
    box.y++;
  }
  if (IsKeyDown(KEY_DOWN)) {
    box.y--;
  }
  if (IsKeyDown(KEY_LEFT)) {
    box.x--;
    scale = {-1.0, 1.0};
  }
  if (IsKeyDown(KEY_RIGHT)) {
    box.x++;
    scale = {1.0, 1.0};
  }

  anim.update();
}

void Player::draw() {
  anim.draw(Vector2{box.x, box.y}, scale);
}
void Player::unload() { anim.unload(); }
} // namespace potato_bucket
