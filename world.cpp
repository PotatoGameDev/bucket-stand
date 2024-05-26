#include "world.h"
#include "object.h"
#include "player.h"
#include <cstdlib>
#include <raylib.h>
#include <iostream>

namespace potato_bucket {

World::World() : player{0.0, 0.0, 10.0, 10.0}, camera{0}, objects{}, bullets{} {
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
  std::cout << "1" << std::endl; 
  for (auto &b : bullets) {
    b.update();
  }
  std::cout << "2" << std::endl; 
  player.update();
  std::cout << "3" << std::endl; 
  camera.target = Vector2{player.box.x, player.box.y};

  std::cout << secondsSinceLastBullet << std::endl;

  secondsSinceLastBullet += GetFrameTime();  
  if (secondsSinceLastBullet > 3.0) {
    secondsSinceLastBullet = 0.0;
    // Shoot
    std::cout << "Player scale: " << player.scale.x << " " << player.scale.y << std::endl;
    Rectangle brec {player.box.x, player.box.y, 6.0f, 4.0f};
    float signX = (player.scale.x < 0.0 ? -1.0 : 1.0);
    float signY = (player.scale.y < 0.0 ? -1.0 : 1.0);
    Vector2 bvel {signX * 1.0f + player.velocity.x, signY * 0.0f + player.velocity.y};
    std::cout << "Bullet velocity: " << bvel.x << " " << bvel.y << std::endl;
    bullets.emplace_back(brec, bvel);
  }
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
  for (auto &b : bullets) {
    b.draw();
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
}

} // namespace potato_bucket
