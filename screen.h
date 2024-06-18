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
  Repeat,
  MainMenu,
  Exit,
  Credits,
  Summary,
  Introduction
};

// ======================================================================
class Screen {
private:
public:
  ~Screen() = default;

  virtual ScreenFlow update() = 0;
  virtual void draw() = 0;
};

// ======================================================================
class WorldScreen : public Screen {
private:
  World world{};

public:
  WorldScreen();
  ScreenFlow update();
  void draw();
  WorldResult result();
  void start(WorldSettings);
};

// ======================================================================
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

// ======================================================================
class SummaryScreen : public Screen {
private:
public:
  WorldResult result{};
  SummaryScreen();
  ScreenFlow update() override;
  void draw() override;
};

// ======================================================================
struct Credit {
  std::string file;
  std::string author;

  Credit(std::string, std::string);
};

class CreditsScreen : public Screen {
private:
    std::vector<Credit> credits{};
    int framesLeft = 60 * 10;
public:
  WorldResult result{};
  CreditsScreen();
  ScreenFlow update() override;
  void draw() override;
};

} // namespace potato_bucket

#endif
