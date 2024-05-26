#include "bullet.h"
#include "anim.h"
#include <raylib.h>
#include <iostream>
#include <string>

namespace potato_bucket {
Bullet::Bullet(float x, float y, float w, float h, Vector2 _velocity): Bullet(Rectangle{x, y, w, h}, _velocity) {}
Bullet::Bullet(Rectangle r, Vector2 _velocity) : box{r}, velocity {_velocity} {}

void Bullet::update() {
    box.x += velocity.x;
    box.y += velocity.y;
}

void Bullet::draw() {
    DrawRectangleV(Vector2{box.x, box.y}, Vector2{box.width, box.height}, WHITE);
}

void Bullet::unload() {}

} // namespace potato_bucket
