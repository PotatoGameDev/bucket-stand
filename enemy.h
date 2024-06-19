#ifndef POTATO_BUCKET_ENEMY_H
#define POTATO_BUCKET_ENEMY_H

#include "anim.h"
#include "player.h"
#include "raylib.h"
#include <vector>

namespace potato_bucket {

class Enemy {
protected:
  Anim anim;
  float maxSpeed{1.0};
  Vector2 lastNonZeroVelocity = {1.0, 0.0};

public:
  ~Enemy() = default;

  Vector2 scale{1.0, 1.0};
  Rectangle box;
  Vector2 velocity{0.0, 0.0};

  Enemy(Vector2, Anim);

  Enemy(Enemy &&) noexcept;
  Enemy &operator=(Enemy &&) noexcept;

  virtual void update(Player &, int, std::vector<Bullet> &) = 0;
  void draw();
};

class Sheriff : public Enemy {
private:
public:
  ~Sheriff() = default;

  Sheriff(Vector2, Anim);

  Sheriff(Sheriff &&) noexcept;
  Sheriff &operator=(Sheriff &&) noexcept;

  void update(Player &, int, std::vector<Bullet> &);
};

class Spider : public Enemy {
private:
    int bitePower;
public:
  ~Spider() = default;

  Spider(Vector2, Anim, int);

  Spider(Spider &&) noexcept;
  Spider &operator=(Sheriff &&) noexcept;

  void update(Player &, int, std::vector<Bullet> &);
};

} // namespace potato_bucket

#endif
