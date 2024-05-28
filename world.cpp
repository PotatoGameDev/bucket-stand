#include "world.h"
#include "object.h"
#include "player.h"
#include <cstdlib>
#include <iostream>
#include <raylib.h>

namespace potato_bucket {

World::World(unsigned int worldSeed, WorldSettings _settings) : player{0.0, 0.0, 10.0, 10.0, {1.0f, 60}}, camera{0}, settings {_settings} {
  float screenWidth = GetScreenWidth();
  float screenHeight = GetScreenHeight();

  camera.target = (Vector2){screenWidth / 2, screenHeight / 2};
  camera.offset = (Vector2){screenWidth / 2, screenHeight / 2};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  objects.emplace_back(player.box, "tree.png");

  srand(worldSeed);

  backgnd = LoadTexture("ass/sand.png");
}

WorldFlow World::update() {
  frameNo++;

  for (auto &o : objects) {
    o.update();
  }

  for (auto it = bullets.begin(); it != bullets.end(); ) {
    it->update();

    if (it->dead()) {
      it = bullets.erase(it);
    } else {
      it++;
    }
  }

  for (auto &e : enemies) {
    e.update(player, frameNo, bullets);
  }
  player.update(frameNo, bullets);
  camera.target = Vector2{player.box.x, player.box.y};

  // Generate enemies
  if (frameNo % (5 * 60) == 0) {
    int precission = 100;
    float randY =
        ((rand() % (2 * 200 * precission)) / static_cast<float>(precission)) -
        200.0f;

    Rectangle enemyBox{player.box.x + 400.0f, player.box.y + randY, 10.0f, 10.0f};
    enemies.emplace_back(enemyBox);
  }

  return WorldFlow::None;
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
}
} // namespace potato_bucket
