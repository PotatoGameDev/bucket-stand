#ifndef POTATO_BUCKET_SCREEN_H
#define POTATO_BUCKET_SCREEN_H

#include "gamestate.h"
#include "gui.h"
#include "raylib.h"
#include "world.h"
#include <cwchar>
#include <memory>
#include <optional>

namespace potato_bucket {

struct WorldScreenSettings {};

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
  std::optional<World> world;
  const std::shared_ptr<GameState> &gameState;

public:
  WorldScreen(const std::shared_ptr<GameState> &);
  ScreenFlow update();
  void draw();
  WorldResult result();
  void start(WorldSettings);
};

// ======================================================================
struct MainMenuScreenSettings {
  int mainTextSize = 25;
  std::string mainText = "DEPRESS [ENTER] TO PLAY";
  Color mainTextColor = WHITE;
};

class MainMenuScreen : public Screen {
private:
  MainMenuScreenSettings settings;
  int mainTextWidth{};
  std::vector<std::unique_ptr<Button>> buttons;
  Button *selectedButton = nullptr;

public:
  MainMenuScreen(MainMenuScreenSettings = {});
  ScreenFlow update() override;
  void draw() override;
};

// ======================================================================

class PerksScreen : public Screen {
private:
  std::vector<std::unique_ptr<PerkButton>> perks;
  PerkButton *selectedPerk = nullptr;
  const std::shared_ptr<GameState> &gameState;

public:
  PerksScreen(const std::shared_ptr<GameState> &);
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
