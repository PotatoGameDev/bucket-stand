#include "enemy.h"
#include "anim.h"
#include "audio_manager.h"
#include "raymath.h"
#include <raylib.h>
#include <string>

namespace potato_bucket {

void Enemy::draw() {
  anim.draw(Vector2{box.x, box.y}, box, scale);
}

Enemy::Enemy(Vector2 position, Anim anim)
    : box{position.x, position.y, 0.0, 0.0}, anim{std::move(anim)},
      scale{1.0, 1.0}, velocity{0.0, 0.0} {
  box.width = anim.width;
  box.height = anim.height;
}

Enemy::Enemy(Enemy &&other) noexcept
    : box{other.box}, anim(std::move(other.anim)), scale{other.scale},
      velocity{other.velocity}, lastNonZeroVelocity{other.lastNonZeroVelocity},
      maxSpeed{other.maxSpeed} { }

Enemy &Enemy::operator=(Enemy&&other) noexcept {
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

// ====================================================
// =================== Sheriff ========================
// ====================================================


Sheriff::Sheriff(Vector2 position, Anim anim) : Enemy(position, std::move(anim)) {}

void Sheriff::update(Player &player, int frameNo, std::vector<Bullet> &bullets) {
  Vector2 playerPos{player.box.x, player.box.y};
  Vector2 enemyPos{box.x, box.y};

  Vector2 toSheriff = Vector2Subtract(playerPos, enemyPos);

  if (toSheriff.x < 0.0f) {
    scale.x = -1.0f;
  } else {
    scale.x = 1.0;
  }

  velocity = Vector2ClampValue(toSheriff, 0.0, maxSpeed);

  float distance = Vector2LengthSqr(toSheriff);
  int stopThreshold = 100;
  stopThreshold *= stopThreshold;
  int retreatThreshold = 80;
  retreatThreshold *= retreatThreshold;

  if (distance < stopThreshold) {
      if (distance < retreatThreshold) {
        velocity = Vector2Scale(velocity, -1);
      } else {
        velocity = Vector2Zero();
      }
  }

  box.x += velocity.x;
  box.y += velocity.y;

  if (!Vector2Equals(velocity, Vector2Zero())) {
    lastNonZeroVelocity = velocity;
  }

  // Generate bullets
  if (frameNo % (1 * 60) == 0) {
    Rectangle brec{box.x + box.width / 2, box.y + box.height / 2, 6.0f, 4.0f};
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

// ====================================================
// ==================== Spider ========================
// ====================================================


Spider::Spider(Vector2 position, Anim anim, int bitePower) : Enemy(position, std::move(anim)), bitePower{bitePower} {}

void Spider::update(Player &player, int frameNo, std::vector<Bullet> &bullets) {
  Vector2 playerPos{player.box.x, player.box.y};
  Vector2 enemyPos{box.x, box.y};

  Vector2 toSpider = Vector2Subtract(playerPos, enemyPos);

  if (toSpider.x < 0.0f) {
    scale.x = -1.0f;
  } else {
    scale.x = 1.0;
  }

  velocity = Vector2ClampValue(toSpider, 0.0, maxSpeed);

  box.x += velocity.x;
  box.y += velocity.y;

  if (!Vector2Equals(velocity, Vector2Zero())) {
    lastNonZeroVelocity = velocity;
  }

  if (CheckCollisionRecs(box, player.box)) {
    if (frameNo % (1 * 60) == 0) {
      player.currentLife -= bitePower;
    }
  }

  anim.update();
}
} // namespace potato_bucket
