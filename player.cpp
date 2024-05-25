#include "player.h"
#include <raylib.h>

namespace potato_bucket {
Player::Player(float x, float y, float w, float h) : box{x, y, w, h} {}

void Player::update() {
    if (IsKeyDown(KEY_UP)) {
        box.y++;
    }
    if (IsKeyDown(KEY_DOWN)) {
        box.y--;
    }
    if (IsKeyDown(KEY_LEFT)) {
        box.x--;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        box.x++;
    }
}

void Player::draw() {
  DrawRectangleRec(box, GetColor(0xFFFFFFFF));
}
} // namespace potato_bucket
