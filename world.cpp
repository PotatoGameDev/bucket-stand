#include "world.h"
#include "player.h"

namespace potato_bucket {

World::World(float screenWidth, float screenHeight)
    : player{0.0, 0.0, 10.0, 10.0}, camera{0} {
  camera.target = (Vector2){screenWidth / 2, screenHeight / 2};
  camera.offset = (Vector2){screenWidth / 2, screenHeight / 2};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
}

void World::update() {
  player.update();
  camera.target = Vector2{player.box.x, player.box.y};
}

void World::draw() { player.draw(); }

} // namespace potato_bucket
