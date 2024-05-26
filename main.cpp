#include "player.h"
#include "raylib.h"
#include "world.h"

using namespace potato_bucket;

int main() {
  int screenWidth = 800;
  int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "BucketStand");

  SetTargetFPS(60);

  World world(0);

  while (!WindowShouldClose()) {

    world.update();

    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(world.camera);

    world.draw();

    EndMode2D();

    DrawFPS(10, 10);
    EndDrawing();
  }

  world.unload();
  CloseWindow();
  return 0;
}
