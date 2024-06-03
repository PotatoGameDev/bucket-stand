#include "world.h"
#include "object.h"
#include "player.h"
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
    : player{0.0, 0.0, {100.f, 1.0f, 10}}, camera{0}, settings{settings} {
  float screenWidth = GetScreenWidth();
  float screenHeight = GetScreenHeight();

  camera.target = (Vector2){screenWidth / 2, screenHeight / 2};
  camera.offset = (Vector2){screenWidth / 2, screenHeight / 2};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  srand(worldSeed);

  objects.emplace_back(player.box.x, player.box.y, "tree.png");
  backgnd = LoadTexture("ass/sand.png");
}

WorldFlow World::update() {
  frameNo++;

  for (auto bu = bullets.begin(); bu != bullets.end();) {
    bu->update();

    if (bu->dead()) {
      bu = bullets.erase(bu);
      continue;
    }

    if (bu->playerBullet) {
      // This handles collisions bullet/enemy
      bool hit = false;
      // std::cout << "bullet / enemy col" << std::endl;
      for (auto en = enemies.begin(); en != enemies.end();) {
        if (CheckCollisionRecs(bu->box, en->box)) {
          // enemy killed
          en = enemies.erase(en);
          hit = true;
          player.currentScore++;
          break;
        }

        en++;
      }
      if (hit) {
        bu = bullets.erase(bu);
        continue;
      }
    } else {
      if (CheckCollisionRecs(bu->box, player.box)) {
        player.currentLife -= 10;
        bu = bullets.erase(bu);
        continue;
      }
    }

    // This handles collisions bullet/bullet
    // std::cout << "bullet / bullet col" << std::endl;
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

  std::cout << "updating objects" << std::endl;
  for (auto &o : objects) {
    o.update();
  }

  std::cout << "updating enemies" << std::endl;
  for (auto &e : enemies) {
    std::cout << "before update enemies" << std::endl;
    e.update(player, frameNo, bullets);
    std::cout << "after update enemies" << std::endl;
  }

  std::cout << "updating player" << std::endl;
  Vector2 playerVelocity = player.update(frameNo, bullets, camera);
  
  Rectangle playerNewBox = player.box;
  playerNewBox.x += playerVelocity.x;
  playerNewBox.y += playerVelocity.y;

  if (playerNewBox.x > GetScreenWidth() / 2 || playerNewBox.x < -GetScreenWidth() / 2) {
      playerNewBox.x = player.box.x;
  }
  if (playerNewBox.y > GetScreenHeight() / 2 || playerNewBox.y < -GetScreenHeight() / 2) {
      playerNewBox.y = player.box.y;
  }

  player.velocity = playerVelocity;
  player.box = playerNewBox;

  camera.target = Vector2{player.box.x, player.box.y};

  std::cout << "gening ens" << std::endl;
  // Generate enemies
  if (frameNo % (5 * 60) == 0) {
    int precission = 100;
    float randY =
        ((rand() % (2 * 200 * precission)) / static_cast<float>(precission)) -
        200.0f;

    Vector2 enemyBox{player.box.x + 400.0f, player.box.y + randY};
    std::cout << "enem gening" << std::endl;
    enemies.emplace_back(enemyBox);
    std::cout << "enem gened" << std::endl;
  }

  std::cout << "up end" << std::endl;

  if (player.currentScore >= settings.winCondition) {
    return WorldFlow::Win;
  }
  if (player.currentLife <= 0.0f) {
    return WorldFlow::Lose;
  }

  return WorldFlow::None;
}

void PrintRectum(const Rectangle& rect) {
    std::cout << "Rectangle(" << rect.x << ", " << rect.y << ", " 
              << rect.width << ", " << rect.height << ")" << std::endl;
}


void PrintVectorum(const Vector2& vect) {
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
