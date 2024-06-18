#include "world.h"
#include "anim.h"
#include "object.h"
#include "player.h"
#include "texture_cache.h"
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <string>

namespace potato_bucket {

WorldSettings::WorldSettings(int winCondition, std::string location,
                             std::string nextLocation)
    : winCondition{winCondition}, location{location},
      nextLocation{nextLocation} {}

World::World() : camera{0}, settings{}, player{0.0, 0.0, {}} {}

World::World(unsigned int worldSeed, WorldSettings settings)
    : player{0.0, 0.0, {500.f, 2.0f, 30}}, camera{0}, settings{settings} {
  float screenWidth = GetScreenWidth();
  float screenHeight = GetScreenHeight();

  camera.target = (Vector2){screenWidth / 2, screenHeight / 2};
  camera.offset = (Vector2){screenWidth / 2, screenHeight / 2};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  srand(worldSeed);

  objects.emplace_back(player.box.x, player.box.y, "tree.png");

  for (int i{-GetScreenWidth() - 50}; i < GetScreenWidth() + 50; i += 20) {
    int bushNo = rand() % 3;
    objects.emplace_back(i, GetScreenHeight(),
                         "bush" + std::to_string(bushNo) + ".png");
    bushNo = rand() % 3;
    objects.emplace_back(i, -GetScreenHeight(),
                         "bush" + std::to_string(bushNo) + ".png");
  }
  for (int i{-GetScreenHeight() - 50}; i < GetScreenHeight() + 50; i += 20) {
    int bushNo = rand() % 3;
    objects.emplace_back(GetScreenWidth(), i,
                         "bush" + std::to_string(bushNo) + ".png");
    bushNo = rand() % 3;
    objects.emplace_back(-GetScreenWidth(), i,
                         "bush" + std::to_string(bushNo) + ".png");
  }

  backgnd = LoadTexture("ass/sand.png");
}

WorldFlow World::update() {
  frameNo++;

  for (auto bu = bullets.begin(); bu != bullets.end();) {
    bu->update();

    if (bu->dead()) {
      bu = bullets.erase(bu);
    TextureCache::Instance().print("bullet erased");
      continue;
    }

    TextureCache::Instance().print("before bullets check");
    if (bu->playerBullet) {
      // This handles collisions bullet/enemy
      bool hit = false;
      // std::cout << "bullet / enemy col" << std::endl;
      for (auto en = enemies.begin(); en != enemies.end();) {
        if (CheckCollisionRecs(bu->box, en->box)) {
          // enemy killed
          TextureCache::Instance().print("before enemy erase");
          en = enemies.erase(en);
          TextureCache::Instance().print("after enemy erase");
          hit = true;
          player.currentScore++;
          break;
        }

        en++;
      }
      if (hit) {
        bu = bullets.erase(bu);
    TextureCache::Instance().print("bullet erased enemy");
        continue;
      }
    } else {
      if (CheckCollisionRecs(bu->box, player.box)) {
        player.currentLife -= 10;
        bu = bullets.erase(bu);
    TextureCache::Instance().print("bullet erased player");
        continue;
      }
    }

    // This handles collisions bullet/bullet
    std::cout << "bullet / bullet col" << std::endl;
    for (auto ob = bullets.begin(); ob != bullets.end();) {
      if (bu == ob) {
        ob++;
        continue;
      }
      if (CheckCollisionRecs(bu->box, ob->box)) {
        Vector2 obVel = ob->velocity;
        Vector2 buVel = bu->velocity;
        bu->bounce(obVel);
        ob->bounce(buVel);
      }

      ob++;
    }

    bu++;
  }

    TextureCache::Instance().print("after collisions");
  std::cout << "updating objects" << std::endl;
  for (auto &o : objects) {
    o.update();
  }

    TextureCache::Instance().print("after updating");
  std::cout << "updating enemies" << std::endl;
  for (auto &e : enemies) {
    std::cout << "before update enemies" << std::endl;
    e.update(player, frameNo, bullets);
    std::cout << "after update enemies" << std::endl;
  }

    TextureCache::Instance().print("after updating enemies");
  std::cout << "updating player" << std::endl;
  Vector2 playerVelocity = player.update(frameNo, bullets, camera);
    TextureCache::Instance().print("after updating player");

  Rectangle playerNewBox = player.box;
  playerNewBox.x += playerVelocity.x;
  playerNewBox.y += playerVelocity.y;

  if (playerNewBox.x > GetScreenWidth() || playerNewBox.x < -GetScreenWidth()) {
    playerNewBox.x = player.box.x;
  }
  if (playerNewBox.y > GetScreenHeight() ||
      playerNewBox.y < -GetScreenHeight()) {
    playerNewBox.y = player.box.y;
  }

  player.velocity = playerVelocity;
  player.box = playerNewBox;

  camera.target = Vector2{player.box.x, player.box.y};

  std::cout << "gening ens" << std::endl;
  // Generate enemies

    TextureCache::Instance().print("before gening");
  if (frameNo % (5 * 60) == 0) {
    int precission = 100;

    float randXMultiplier = rand() % 2;
    if (randXMultiplier == 0) {
      randXMultiplier = -1;
    }

    float randX = GetScreenWidth() * randXMultiplier + 50;
    float randY = rand() % 2 * GetScreenHeight() - GetScreenHeight();

    Vector2 enemyBox{randX, randY};

    int enemType = rand() % 2;

    std::cout << "============================================" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "enem gening " << enemType << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "============================================" << std::endl;

    if (enemType == 0) {
      enemies.emplace_back(enemyBox, Anim{"enemy.png", 6});
    } else if (enemType == 1) {
      enemies.emplace_back(enemyBox, Anim{"spider.png", 6});
    }

    std::cout << "enem gened" << std::endl;
  }

  std::cout << "up end" << std::endl;
    TextureCache::Instance().print("after gening");

  if (player.currentScore >= settings.winCondition) {
    return WorldFlow::Win;
  }
  if (player.currentLife <= 0.0f) {
    return WorldFlow::Lose;
  }

  return WorldFlow::None;
}

void PrintRectum(const Rectangle &rect) {
  std::cout << "Rectangle(" << rect.x << ", " << rect.y << ", " << rect.width
            << ", " << rect.height << ")" << std::endl;
}

void PrintVectorum(const Vector2 &vect) {
  std::cout << "Rectangle(" << vect.x << ", " << vect.y << ")" << std::endl;
}

WorldResult World::result() {
  if (player.currentScore >= settings.winCondition) {
    return {player.currentScore, true, settings.location,
            settings.nextLocation};
  }
  return {player.currentScore, false, settings.location, settings.nextLocation};
}

void World::draw() {
  BeginMode2D(camera);

  float screenWidth = GetScreenWidth();
  float screenHeight = GetScreenHeight();

  int xtiles = screenWidth / backgnd.width + 1;
  int ytiles = screenHeight / backgnd.height + 1;

  for (int i = 0; i < xtiles; i++) {
    for (int j = 0; j < ytiles; j++) {
      Vector2 pos = {static_cast<float>(i * backgnd.width) -
                         (xtiles * (float)backgnd.width / 2),
                     static_cast<float>(j * backgnd.height) -
                         (ytiles * (float)backgnd.height / 2)};

      DrawTextureV(backgnd, pos, WHITE);
    }
  }

  for (auto &o : objects) {
    o.draw();
  }
  for (auto &b : bullets) {
    b.draw();
  }
  for (auto &e : enemies) {
    e.draw();
  }

  player.draw();

  EndMode2D();

  //=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
  // Draw GUI

  std::string scoreText =
      "killed: " + std::to_string(player.currentScore) +
      " left: " + std::to_string(settings.winCondition - player.currentScore);
  DrawText(scoreText.c_str(),
           GetScreenWidth() / 2 - MeasureText(scoreText.c_str(), 25) / 2, 10,
           25, WHITE);

  Color lifeColor = player.currentLife > 30 ? GREEN : RED;

  DrawRectangleRec({GetScreenWidth() / 2 - player.currentLife / 2, 40,
                    player.currentLife, 10},
                   lifeColor);
}
} // namespace potato_bucket
