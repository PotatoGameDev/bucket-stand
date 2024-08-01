#include "screen.h"
#include "gamestate.h"
#include "gui.h"
#include "logging.h"
#include "matildas.h"
#include "screenflow.h"
#include "world.h"
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <raylib.h>
#include <string>

namespace potato_bucket {

// ======================================================================
//                             WorldScreen
// ======================================================================
WorldScreen::WorldScreen() {}

ScreenFlow WorldScreen::update() {
  WorldFlow result = world.update();

  if (result == WorldFlow::Win) {
    return ScreenFlow::Perks;
  }

  if (result == WorldFlow::Lose) {
    return ScreenFlow::Perks;
  }

  if (IsKeyPressed(KEY_ESCAPE)) {
    return ScreenFlow::MainMenu;
  }

  return ScreenFlow::None;
}

WorldResult WorldScreen::result() { return world.result(); }

void WorldScreen::start(WorldSettings settings) {
  world = {0, settings};

  Matildas::Instance().giveMeNextOne();
}

void WorldScreen::draw() { world.draw(); }

// ======================================================================
//                              MainMenuScreen
// ======================================================================
MainMenuScreen::MainMenuScreen(MainMenuScreenSettings settings)
    : settings{settings} {
  buttons.push_back(std::make_unique<Button>(Vector2{0.5, 0.2}, "Credits",
                                             ScreenFlow::Credits));
  Button *creditsButton = buttons.back().get();

  // buttons.push_back(std::make_unique<Button>( Vector2{0.5, 0.39},
  // settings.mainText, ScreenFlow::Introduction));
  buttons.push_back(std::make_unique<Button>(
      Vector2{0.5, 0.39}, settings.mainText, ScreenFlow::Perks));
  Button *startButton = buttons.back().get();
  startButton->setFontSize(settings.mainTextSize);
  startButton->fontColor = settings.mainTextColor;
  selectedButton = startButton;
  selectedButton->selected = true;

  buttons.push_back(
      std::make_unique<CheckButton>(Vector2{0.5, 0.7}, "MUTE", "UNMUTE"));
  Button *muteButton = buttons.back().get();

  buttons.push_back(
      std::make_unique<Button>(Vector2{0.5, 0.9}, "EXIT", ScreenFlow::Exit));
  Button *exitButton = buttons.back().get();

  creditsButton->down = startButton;
  startButton->down = muteButton;
  muteButton->down = exitButton;

  exitButton->up = muteButton;
  muteButton->up = startButton;
  startButton->up = creditsButton;
};

ScreenFlow MainMenuScreen::update() {
  if (IsKeyPressed(KEY_ESCAPE)) {
    return ScreenFlow::Exit;
  }

  // This handles the mouse mode:
  for (auto &butt : buttons) {
    Button *newSelected = butt->update();

    if (newSelected != nullptr) {
      if (selectedButton != nullptr) {
        selectedButton->selected = false;
      }
      selectedButton = newSelected;
      selectedButton->selected = true;
    }

    if (butt->pressed()) {
      return butt->doAction();
    }
  }

  // This handles the keyboard mode:
  if (selectedButton != nullptr) {
    if (selectedButton->down != nullptr &&
        (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_D) ||
         IsKeyPressed(KEY_J))) {
      selectedButton->selected = false;
      selectedButton = selectedButton->down;
      selectedButton->selected = true;
    } else if (selectedButton->up != nullptr &&
               (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_E) ||
                IsKeyPressed(KEY_K))) {
      selectedButton->selected = false;
      selectedButton = selectedButton->up;
      selectedButton->selected = true;
    }
  }

  if (IsKeyPressed(KEY_ENTER)) {
    if (selectedButton != nullptr) {
      return selectedButton->doAction();
    }
  }

  return ScreenFlow::None;
}

void MainMenuScreen::draw() {
  for (auto &butt : buttons) {
    butt->draw();
  }
}

// ======================================================================
//                             PerksScreen
// ======================================================================
PerksScreen::PerksScreen(const std::shared_ptr<GameState> &gameState)
    : gameState{gameState} {
  std::vector<std::string> perkNames{
      "CHAIN REACTION",
      "STEAL BULLETS",
      "BACKWARDS",
  };

  std::vector<std::string> perkDescriptions{
      "PLAYER BULLETS SPLIT IN TWO SMALLER WHEN THEY HIT ENEMY BULLETS",
      "PLAYER BULLETS CONVERT ENEMY BULLETS INTO PLAYER BULLETS",
      "PLAYER CAN ONLY WALK BACKWARDS",
  };

  // This calculates perks positions:
  float yOffset = 0;
  for (size_t i = 0; i < PERKS_COUNT; i++) {
    float c = static_cast<float>(i);
    Perk p = static_cast<Perk>(i);
    LOG(p);
    perks.push_back(std::make_unique<PerkButton>(
        p,
        Vector2{0.01f + (0.5f * (i % 2)),
                0.2f + (c * 0.1f) - (i % 2) * 0.1f - yOffset},
        0.45f, perkNames[c], perkDescriptions[c], gameState));
    auto lastAdded = perks.back().get();

    yOffset = 0.05f * static_cast<int>((i + 1) / 2);
  }

  for (size_t i = 0; i < PERKS_COUNT; i++) {
    if (i > 1) {
      perks[i]->up = perks[i - 2].get();
    }
    if (i < perks.size() - 2) {
      perks[i]->down = perks[i + 2].get();
    }
    if (i % 2 == 0 && i < perks.size() - 1) {
      perks[i]->right = perks[i + 1].get();
    }
    if (i % 2 == 1 && i > 0) {
      perks[i]->left = perks[i - 1].get();
    }
  }
}

ScreenFlow PerksScreen::update() {
  if (IsKeyPressed(KEY_ESCAPE)) {
    // return ScreenFlow::Exit;
    return ScreenFlow::Repeat;
  }

  // This handles the mouse mode:
  PerkButton *newSelected = nullptr;
  for (auto &perk : perks) {
    PerkButton *updateResult = static_cast<PerkButton *>(perk->update());

    if (updateResult != nullptr) {
      newSelected = updateResult;
    }

    if (perk->pressed()) {
      perk->doAction();
    }
  }

  if (newSelected != nullptr) {
    if (selectedPerk != nullptr) {
      selectedPerk->selected = false;
    }
    selectedPerk = newSelected;
    selectedPerk->selected = true;
  }

  if (IsKeyPressed(KEY_ENTER)) {
    selectedPerk->doAction();
  }

  return ScreenFlow::None;
}

void PerksScreen::draw() {

  // Draws a border for the available perk counters
  float topPanelX = GetScreenWidth() / 4.0f;
  float topPanelY = 1.0f;
  float topPanelWidth{GetScreenWidth() * 0.5f};
  float topPanelHeight{GetScreenHeight() * 0.1f};
  DrawRectangleLinesEx({topPanelX, topPanelY, topPanelWidth, topPanelHeight},
                       2.0, WHITE);

  // Draws available perks:
  float perkHeight{topPanelHeight - 2};
  float perkWidth{topPanelWidth / PERKS_COUNT};
  for (int i = 0; i < PERKS_COUNT; i++) {
    Color color = GREEN;
    if (PERKS_COUNT - gameState->getPerksUsed() < i + 1) {
      color = BLACK;
    }
    DrawRectangleRec(
        {topPanelX + i * perkWidth, topPanelY + 1.0f, perkWidth, perkHeight},
        color);
    DrawRectangleLinesEx(
        {topPanelX + i * perkWidth, topPanelY + 1.0f, perkWidth, perkHeight},
        2.0f, DARKGREEN);
  }

  for (auto &perk : perks) {
    perk->draw();
  }

  // Draws a border for the perk description
  float descPanelWidth{GetScreenWidth() - 2.0f};
  float descPanelHeight{GetScreenHeight() * 0.1f};
  float descPanelX = 0.1;
  float descPanelY = GetScreenHeight() - descPanelHeight;
  DrawRectangleLinesEx(
      {descPanelX, descPanelY, descPanelWidth, descPanelHeight}, 2.0, WHITE);

  if (selectedPerk != nullptr) {
    int descTextSize = 20;
    DrawText(selectedPerk->description.c_str(),
             (GetScreenWidth() - selectedPerk->descriptionWidth) / 2.0f,
             descPanelY + (descPanelHeight / 2.0f) - descTextSize / 2.0f,
             descTextSize, WHITE);
  }
}

// ======================================================================
//                              SummaryScreen
// ======================================================================
SummaryScreen::SummaryScreen(){};

ScreenFlow SummaryScreen::update() {
  if (IsKeyPressed(KEY_ENTER)) {
    if (result.win) {
      return ScreenFlow::NextWorld;
    } else {
      return ScreenFlow::Repeat;
    }
  }

  if (IsKeyPressed(KEY_ESCAPE)) {
    return ScreenFlow::MainMenu;
  }

  return ScreenFlow::None;
}

void SummaryScreen::draw() {
  int line{};
  int lines = 9;

  std::string text1{};
  int text1Size = 26;
  float text1Width = 0;

  int vert = 20;

  if (result.intro) {
    lines = 9;
    text1 = "A GREAT AUSIE HERO NED KELLY";
    text1Size = 26;
    text1Width = MeasureText(text1.c_str(), text1Size);
    DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
             vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

    text1 = "TIRED OF THE OPRESSION FROM THE BRITISH LIZARD MEN";
    text1Size = 26;
    text1Width = MeasureText(text1.c_str(), text1Size);
    DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
             vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

    text1 = "PUT A BUCKET ON HIS HEAD AND STARTED";
    text1Size = 26;
    text1Width = MeasureText(text1.c_str(), text1Size);
    DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
             vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

    text1 = "WHAT WE NOW CALL";
    text1Size = 26;
    text1Width = MeasureText(text1.c_str(), text1Size);
    DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
             vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

    text1 = "'THE GREAT LIBERATION WAR OF AUSTRALIA'";
    text1Size = 26;
    text1Width = MeasureText(text1.c_str(), text1Size);
    DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
             vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

    text1 = "HE STARTED HIS ADVENTURE IN " + result.nextLocation;
    text1Size = 26;
    text1Width = MeasureText(text1.c_str(), text1Size);
    DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
             vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

    text1 = "EVERYTHING IN THIS GAME IS TOTALLY FACTUAL";
    text1Size = 16;
    text1Width = MeasureText(text1.c_str(), text1Size);
    DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
             vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);
  } else {
    lines = 9;
    text1 = "AFTER A BRAVE FIGHT IN";
    text1Size = 26;
    text1Width = MeasureText(text1.c_str(), text1Size);
    DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
             vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

    text1 = result.location;
    text1Size = 26;
    text1Width = MeasureText(text1.c_str(), text1Size);
    DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
             vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

    text1 = "NED KELLY DEFEATED";
    text1Size = 26;
    text1Width = MeasureText(text1.c_str(), text1Size);
    DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
             vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

    text1 = std::to_string(result.killed) + " ENEMIES";
    text1Size = 26;
    text1Width = MeasureText(text1.c_str(), text1Size);
    DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
             vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

    if (!result.win) {
      std::string text2{"THIS WAS HIS"};
      int text2Size = 26;
      float text2Width = MeasureText(text2.c_str(), text2Size);
      DrawText(text2.c_str(), (GetScreenWidth() - text2Width) / 2,
               vert + line++ * GetScreenHeight() / lines, text2Size, WHITE);

      std::string text3{"LAST STAND"};
      int text3Size = 56;
      float text3Width = MeasureText(text3.c_str(), text3Size);
      DrawText(text3.c_str(), (GetScreenWidth() - text3Width) / 2,
               vert + line++ * GetScreenHeight() / lines, text3Size, WHITE);
    } else {
      std::string text2{"THEN HE FAMOUSLY MOVED TO " + result.nextLocation};
      int text2Size = 26;
      float text2Width = MeasureText(text2.c_str(), text2Size);
      DrawText(text2.c_str(), (GetScreenWidth() - text2Width) / 2,
               vert + line++ * GetScreenHeight() / lines, text2Size, WHITE);
    }
  }

  std::string text4 = "DEPRESS [ENTER] ";
  if (result.win) {
    text4 += "FOR NEXT LEVEL";
  } else {
    text4 += "TO TRY AGAIN";
  }
  text4 += " OR [ESC] TO EXIT";

  int text4Size = 26;
  float text4Width = MeasureText(text4.c_str(), text4Size);
  DrawText(text4.c_str(), (GetScreenWidth() - text4Width) / 2,
           vert + line++ * GetScreenHeight() / lines, text4Size, WHITE);
}

// ======================================================================
//                              CreditsScreen
// ======================================================================
ScreenFlow CreditsScreen::update() {
  if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE) ||
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || framesLeft <= 0) {
    return ScreenFlow::MainMenu;
  }
  framesLeft--;

  return ScreenFlow::None;
}

CreditsScreen::CreditsScreen() {
  credits.emplace_back(
      "https://commons.wikimedia.org/wiki/File:Waltzing_Matilda.ogg",
      "CambridgeBayWeather, CC BY-SA 3.0 "
      "<https://creativecommons.org/licenses/by-sa/3.0>, via Wikimedia "
      "Commons");
  credits.emplace_back(
      "https://commons.wikimedia.org/wiki/"
      "File:Waltzing-Matilda-_Christina-Macpherson_-Wikipedia.ogg",
      "BDW82, CC BY-SA 4.0 <https://creativecommons.org/licenses/by-sa/4.0>, "
      "via Wikimedia Commons");
  credits.emplace_back("https://opengameart.org/content/giant-spider-32x32",
                       "Spider made by Tuomo Untinen");
  credits.emplace_back("https://opengameart.org/content/100-isometric-bushes",
                       "Hansjörg Malthaner, and link here: "
                       "http://opengameart.org/users/varkalandar");
}

Credit::Credit(std::string file, std::string author)
    : file{file}, author{author} {}

void CreditsScreen::draw() {
  int line{};
  int lines = credits.size() * 2 + 5;

  std::string text1{};
  int text1Size = 26;
  float text1Width = 0;

  int vert = 20;

  text1 = "by potatogam.es";
  text1Size = 24;
  text1Width = MeasureText(text1.c_str(), text1Size);
  DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
           vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

  text1 = "PLEASE VISIT MY STREAM TO SEE HOW I MADE THIS";
  text1Size = 20;
  text1Width = MeasureText(text1.c_str(), text1Size);
  DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
           vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

  text1 = "https://www.twitch.tv/potatogamedev";
  text1Size = 20;
  text1Width = MeasureText(text1.c_str(), text1Size);
  DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
           vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

  text1 = "Open Source: https://github.com/PotatoGameDev/bucket-stand";
  text1Size = 20;
  text1Width = MeasureText(text1.c_str(), text1Size);
  DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
           vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

  int i = 1;
  for (auto cred : credits) {
    text1 = cred.file;
    text1Size = 12;
    text1Width = MeasureText(text1.c_str(), text1Size);
    DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
             vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

    text1 = cred.author;
    text1Size = 12;
    text1Width = MeasureText(text1.c_str(), text1Size);
    DrawText(text1.c_str(), (GetScreenWidth() - text1Width) / 2,
             vert + line++ * GetScreenHeight() / lines, text1Size, WHITE);

    line++;
  }
}
} // namespace potato_bucket
