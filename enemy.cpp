#include "enemy.h"
#include "audio_manager.h"
#include "raymath.h"
#include <iostream>
#include <raylib.h>

namespace potato_bucket {
Enemy::Enemy(Vector2 position)
    : box{position.x, position.y, 0.0, 0.0}, anim("enemy.png", 6),
      scale{1.0, 1.0}, velocity{0.0, 0.0} {
  box.width = anim.width;
  box.height = anim.height;
  std::cout << "created enemy" << std::endl;
}

Enemy::Enemy(float x, float y)
    : Enemy(Vector2{x, y}) {}

Enemy::Enemy(Enemy &&other) noexcept
    : box{other.box}, anim(std::move(other.anim)), scale{other.scale},
      velocity{other.velocity} {}

Enemy &Enemy::operator=(Enemy &&other) noexcept {
  if (this != &other) {
    anim = std::move(other.anim);
    maxSpeed = other.maxSpeed;
    lastNonZeroVelocity = other.lastNonZeroVelocity;
    scale = other.scale;
    box = other.box;
    velocity = other.velocity;
  }
  return *this;
}

void Enemy::update(Player &player, int frameNo, std::vector<Bullet> &bullets) {
  Vector2 playerPos{player.box.x, player.box.y};
  Vector2 enemyPos{box.x, box.y};

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
  if (frameNo % (1 * 60) == 0) {
    Rectangle brec{box.x + box.width/2, box.y + box.height/2, 6.0f, 4.0f};
    float signX = (scale.x < 0.0 ? -1.0 : 1.0);
    float signY = (scale.y < 0.0 ? -1.0 : 1.0);

    float bulletSpeed = 1.0f;
    Vector2 bvel =
        Vector2Add(velocity, Vector2Scale(Vector2Normalize(lastNonZeroVelocity),
                                          bulletSpeed));
    bullets.emplace_back(brec, bvel, 5);
    AudioMan::Instance().play("shoot.wav", playerPos, enemyPos);
  }

  anim.update();
}

void Enemy::draw() {
  anim.draw(Vector2{box.x, box.y}, box, scale);
}
} // namespace potato_bucket
