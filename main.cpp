#include "player.h"
#include "raylib.h"
#include "screen.h"
#include "world.h"
#include <vector>

using namespace potato_bucket;

int main() {
  int screenWidth = 800;
  int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "BucketStand");

  SetTargetFPS(60);

  std::vector<WorldScreen> screens { 
    WorldScreen{}
  };

  int currentScreen = 0;

  while (!WindowShouldClose()) {

      screens[currentScreen].update();

    BeginDrawing();
    ClearBackground(BLACK);

      screens[currentScreen].draw();

    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
