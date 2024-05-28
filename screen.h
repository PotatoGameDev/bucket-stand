#ifndef POTATO_BUCKET_SCREEN_H
#define POTATO_BUCKET_SCREEN_H

#include "raylib.h"
#include "world.h"

namespace potato_bucket {

struct WorldScreenSettings {};

enum class ScreenFlow {

  None,
  FirstWorld,
  NextWorld,
  MainMenu,
  Exit

};

class Screen {
private:
public:
  ~Screen() = default;

  virtual ScreenFlow update() = 0;
  virtual void draw() = 0;
};

class WorldScreen : public Screen {
private:
  World world;

public:
  WorldScreen(WorldScreenSettings = {});
  ScreenFlow update();
  void draw();
};

struct MenuScreenSettings {
  int mainTextSize = 25;
  std::string mainText = "DEPRESS [ENTER] TO PLAY";
  Color mainTextColor = WHITE;
};

class MenuScreen : public Screen {
private:
  MenuScreenSettings settings;
  int mainTextWidth{};

public:
  MenuScreen(MenuScreenSettings = {});
  ScreenFlow update() override;
  void draw() override;
};

} // namespace potato_bucket

#endif
