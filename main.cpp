#include "raylib.h"
#include "screen.h"
#include <memory>
#include <vector>

using namespace potato_bucket;

int main() {
  int screenWidth = 800;
  int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "BucketStand");
  SetTargetFPS(60);
  SetExitKey(0);

  std::vector<std::unique_ptr<Screen>> screens;

  screens.push_back(std::make_unique<WorldScreen>());

  std::unique_ptr<MenuScreen> mainMenuScreen = std::make_unique<MenuScreen>();

  Screen *currentScreen = mainMenuScreen.get();
  int currentWorldIndex = 0;

  while (!WindowShouldClose()) {
    ScreenFlow GOTO = currentScreen->update();
    if (GOTO == ScreenFlow::Exit) {
        break;
    }

    switch(GOTO) {
        case ScreenFlow::FirstWorld:
            currentWorldIndex = 0;
            currentScreen = screens[currentWorldIndex].get();
            break;
        case ScreenFlow::NextWorld:
            currentWorldIndex++;
            currentScreen = screens[currentWorldIndex].get();
            break;
        case ScreenFlow::MainMenu:
            currentScreen = mainMenuScreen.get();
        case ScreenFlow::Exit:
        case ScreenFlow::None:
            break;
    }

    BeginDrawing();
    ClearBackground(BLACK);

    currentScreen->draw();

    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
