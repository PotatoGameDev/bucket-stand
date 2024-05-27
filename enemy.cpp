#include "enemy.h"
#include "raymath.h"
#include <raylib.h>

namespace potato_bucket {
Enemy::Enemy(Rectangle _box)
    : box{_box}, anim("enemy.png", 6, _box.x, _box.y, 48.0, 48.0),
      scale{1.0, 1.0}, velocity{0.0, 0.0} {}

Enemy::Enemy(float x, float y, float w, float h) : Enemy(Rectangle{x, y, w, h}) {}

void Enemy::update(Player player, int frameNo, std::vector<Bullet>& bullets) {
  Vector2 playerPos {player.box.x, player.box.y};
  Vector2 enemyPos {box.x, box.y};

  Vector2 toEnemy = Vector2Subtract(playerPos, enemyPos);

  if (toEnemy.x < 0.0f) {
      scale.x = -1.0f;
  } else {
      scale.x = 1.0;
  }

  velocity = Vector2ClampValue(toEnemy, 0.0, maxSpeed);

  box.x += velocity.x;
  box.y += velocity.y;

  if (!Vector2Equals(velocity, Vector2Zero())) {
      lastNonZeroVelocity = velocity;
  }

  // Generate bullets
  if (frameNo % (3 * 60) == 0) {
    Rectangle brec{box.x, box.y, 6.0f, 4.0f};
    float signX = (scale.x < 0.0 ? -1.0 : 1.0);
    float signY = (scale.y < 0.0 ? -1.0 : 1.0);

    float bulletSpeed = 1.0f;
    Vector2 bvel = Vector2Add(
        velocity, Vector2Scale(Vector2Normalize(lastNonZeroVelocity), bulletSpeed));
    bullets.emplace_back(brec, bvel, 5);
  }

  anim.update();
}

void Enemy::draw() { anim.draw(Vector2{box.x, box.y}, scale); }
void Enemy::unload() { anim.unload(); }
} // namespace potato_bucket
