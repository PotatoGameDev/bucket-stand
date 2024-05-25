#include "player.h"
#include "raylib.h"
#include "world.h"

using namespace potato_bucket;

int main() {
  int screenWidth = 800;
  int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "BucketGang");

  SetTargetFPS(60);

  World world(screenWidth, screenHeight);

  while (!WindowShouldClose()) {

    world.update();

    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(world.camera);

    world.draw();

    EndMode2D();

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
