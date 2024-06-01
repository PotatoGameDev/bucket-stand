#include "raylib.h"
#include "screen.h"
#include "world.h"
#include <iterator>
#include <memory>
#include <vector>

using namespace potato_bucket;

int main() {
  int screenWidth = 800;
  int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "BucketStand");
  SetTargetFPS(60);
  SetExitKey(0);

  std::vector<WorldSettings> levels;

  levels.emplace_back(1, "Beveridge", "Mansfield");
  levels.emplace_back(3, "Mansfield", "Euroa");
  levels.emplace_back(10, "Euroa", "Greta");
  levels.emplace_back(20, "Greta", "Glenrowan");
  levels.emplace_back(50, "Glenrowan", "");

  std::unique_ptr<WorldScreen> worldScreen = std::make_unique<WorldScreen>();
  std::unique_ptr<MenuScreen> mainMenuScreen = std::make_unique<MenuScreen>();
  std::unique_ptr<SummaryScreen> summaryScreen =
      std::make_unique<SummaryScreen>();

  Screen *currentScreen = mainMenuScreen.get();
  int currentLevel = 0;

  while (!WindowShouldClose()) {
    ScreenFlow GOTO = currentScreen->update();
    if (GOTO == ScreenFlow::Exit) {
      break;
    }

    switch (GOTO) {
    case ScreenFlow::Introduction:
      summaryScreen->result = {0, true, "", levels[0].location, true};
      currentScreen = summaryScreen.get();
      break;
    case ScreenFlow::FirstWorld:
      currentLevel = 0;
      worldScreen.get()->start(levels[currentLevel]);
      currentScreen = worldScreen.get();
      break;
    case ScreenFlow::NextWorld:
      currentLevel++;
      if (currentLevel == levels.size()) {
        currentScreen = mainMenuScreen.get();
        break;
      }
      worldScreen.get()->start(levels[currentLevel]);
      currentScreen = worldScreen.get();
      break;
    case ScreenFlow::Repeat:
      worldScreen.get()->start(levels[currentLevel]);
      currentScreen = worldScreen.get();
      break;
    case ScreenFlow::Summary:
      summaryScreen->result = worldScreen->result();
      currentScreen = summaryScreen.get();
      break;
    case ScreenFlow::MainMenu:
      currentScreen = mainMenuScreen.get();
      break;
    case ScreenFlow::Exit:
    case ScreenFlow::None:
      break;
    }

    BeginDrawing();
    ClearBackground(BLACK);

    currentScreen->draw();

    DrawFPS(GetScreenWidth() - 30, 10);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
