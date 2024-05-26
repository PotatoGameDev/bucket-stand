#include "world.h"
#include "object.h"
#include "player.h"
#include <cstdlib>
#include <iostream>
#include <raylib.h>

namespace potato_bucket {

World::World(unsigned int worldSeed) : player{0.0, 0.0, 10.0, 10.0}, camera{0} {
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

void World::update() {
  frameNo++;

  for (auto &o : objects) {
    o.update();
  }
  for (auto &b : bullets) {
    b.update();
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
        ((rand() % (2 * 50 * precission)) / static_cast<float>(precission)) -
        50.0f;

    Rectangle enemyBox{player.box.x + 100.0f, player.box.y + randY, 10.0f,
                       10.0f};
    enemies.emplace_back(enemyBox);
  }
}

void World::draw() {
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
}

void World::unload() {
  player.unload();
  for (auto &o : objects) {
    o.unload();
  }
  for (auto &b : bullets) {
    b.unload();
  }
  for (auto &e : enemies) {
    e.unload();
  }
}

} // namespace potato_bucket
