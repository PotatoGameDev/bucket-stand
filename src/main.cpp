#include "audio_manager.h"
#include "matildas.h"
#include "raylib.h"
#include "screen.h"
#include "texture_cache.h"
#include "world.h"
#include <memory>
#include <vector>
#include "logging.h"

using namespace potato_bucket;

int main() {
  int screenWidth = 800;
  int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "BucketStand");
  SetTargetFPS(60);
  SetExitKey(0);

  InitAudioDevice();

  std::vector<WorldSettings> levels;

  levels.emplace_back(3, "Mansfield", "Euroa");
  levels.emplace_back(10, "Beveridge", "Mansfield");
  levels.emplace_back(20, "Euroa", "Greta");
  levels.emplace_back(30, "Greta", "Glenrowan");
  levels.emplace_back(100, "Glenrowan", "");

  std::unique_ptr<WorldScreen> worldScreen = std::make_unique<WorldScreen>();

  // Move to some text based config file or something, for translations or stuff...
  MainMenuScreenSettings mainMenuScreenSettings{
    50,
    "DEPRESS [ENTER] TO PLAY",
    WHITE,
  };

  std::unique_ptr<MainMenuScreen> mainMenuScreen =
      std::make_unique<MainMenuScreen>(mainMenuScreenSettings);
  std::unique_ptr<SummaryScreen> summaryScreen =
      std::make_unique<SummaryScreen>();
  std::unique_ptr<PerksScreen> perksScreen =
      std::make_unique<PerksScreen>();
  std::unique_ptr<CreditsScreen> creditsScreen =
      std::make_unique<CreditsScreen>();

  Screen *currentScreen = mainMenuScreen.get();
  int currentLevel = 0;

  Matildas::Instance().giveMeNextOne();

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
    case ScreenFlow::Perks:
      currentScreen = perksScreen.get();
      LOG("CHanged to perkd");
      break;
    case ScreenFlow::MainMenu:
      currentScreen = mainMenuScreen.get();
      break;
    case ScreenFlow::Credits:
      currentScreen = creditsScreen.get();
      break;
    case ScreenFlow::Exit:
    case ScreenFlow::None:
      break;
    }

    Matildas::Instance().update();

    BeginDrawing();
    ClearBackground(BLACK);

    currentScreen->draw();

    DrawFPS(GetScreenWidth() - 30, 10);
    EndDrawing();
  }

  // TODO: Handle in destructors instead:
  AudioMan::Instance().unload();
  TextureCache::Instance().unload();
  Matildas::Instance().unload();

  CloseAudioDevice();
  CloseWindow();
  return 0;
}
