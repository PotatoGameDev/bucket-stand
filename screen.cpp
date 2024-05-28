#include "screen.h"
#include "world.h"
#include <cstdlib>
#include <raylib.h>

namespace potato_bucket {

// ======================================================================
//                             WorldScreen
// ======================================================================
WorldScreen::WorldScreen(WorldScreenSettings settings) : world{0, {}} {}

ScreenFlow WorldScreen::update() {
  WorldFlow result = world.update();

  if (result == WorldFlow::Win) {
    return ScreenFlow::NextWorld;
  }

  if (result == WorldFlow::Lose) {
    return ScreenFlow::MainMenu;
  }

  if (IsKeyPressed(KEY_ESCAPE)) {
    return ScreenFlow::MainMenu;
  }

  return ScreenFlow::None;
}

void WorldScreen::draw() { world.draw(); }

// ======================================================================
//                              MenuScreen
// ======================================================================
MenuScreen::MenuScreen(MenuScreenSettings settings) : settings {settings} {
  mainTextWidth = MeasureText(settings.mainText.c_str(), settings.mainTextSize);
};

ScreenFlow MenuScreen::update() {
  if (IsKeyPressed(KEY_ENTER)) {
    return ScreenFlow::FirstWorld;
  }

  if (IsKeyPressed(KEY_ESCAPE)) {
    return ScreenFlow::Exit;
  }

  return ScreenFlow::None;
}

void MenuScreen::draw() {
  DrawText(settings.mainText.c_str(), (GetScreenWidth() - mainTextWidth) / 2, GetScreenHeight() / 2, settings.mainTextSize, settings.mainTextColor);
}
} // namespace potato_bucket
