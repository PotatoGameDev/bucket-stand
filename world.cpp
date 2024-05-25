#include "world.h"
#include "object.h"
#include "player.h"
#include <raylib.h>

namespace potato_bucket {

World::World() : player{0.0, 0.0, 10.0, 10.0}, camera{0}, objects{} {
  float screenWidth = GetScreenWidth();
  float screenHeight = GetScreenHeight();

  camera.target = (Vector2){screenWidth / 2, screenHeight / 2};
  camera.offset = (Vector2){screenWidth / 2, screenHeight / 2};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  objects.emplace_back(player.box, "tree.png");

  backgnd = LoadTexture("ass/sand.png");
}

void World::update() {
  for (auto &o : objects) {
    o.update();
  }
  player.update();
  camera.target = Vector2{player.box.x, player.box.y};
}

void World::draw() {
  float screenWidth = GetScreenWidth();
  float screenHeight = GetScreenHeight();

  int xtiles = screenWidth / backgnd.width + 1;
  int ytiles = screenHeight / backgnd.height + 1;

  for (int i = 0; i < xtiles; i++) {
    for (int j = 0; j < ytiles; j++) {
      Vector2 pos = {static_cast<float>(i * backgnd.width) - (xtiles * (float)backgnd.width / 2),
                     static_cast<float>(j * backgnd.height) - (ytiles * (float)backgnd.height / 2)};

      DrawTextureV(backgnd, pos, WHITE);
    }
  }

  for (auto &o : objects) {
    o.draw();
  }

  player.draw();
}

void World::unload() {
  player.unload();
  for (auto &o : objects) {
    o.unload();
  }
}

} // namespace potato_bucket
