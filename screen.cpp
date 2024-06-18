#include "screen.h"
#include "matildas.h"
#include "world.h"
#include <cstdlib>
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
    return ScreenFlow::Summary;
  }

  if (result == WorldFlow::Lose) {
    return ScreenFlow::Summary;
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
//                              MenuScreen
// ======================================================================
MenuScreen::MenuScreen(MenuScreenSettings settings) : settings{settings} {
  mainTextWidth = MeasureText(settings.mainText.c_str(), settings.mainTextSize);
};

ScreenFlow MenuScreen::update() {
  if (IsKeyPressed(KEY_ENTER)) {
    return ScreenFlow::Introduction;
  }

  if (IsKeyPressed(KEY_ESCAPE)) {
    return ScreenFlow::Credits;
  }

  return ScreenFlow::None;
}

void MenuScreen::draw() {
  DrawText(settings.mainText.c_str(), (GetScreenWidth() - mainTextWidth) / 2,
           GetScreenHeight() / 2, settings.mainTextSize,
           settings.mainTextColor);
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
  if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE) || framesLeft <= 0) {
    return ScreenFlow::Exit;
  }
  framesLeft--;

  return ScreenFlow::None;
}

CreditsScreen::CreditsScreen() {
  credits.emplace_back("https://commons.wikimedia.org/wiki/File:Waltzing_Matilda.ogg", "CambridgeBayWeather, CC BY-SA 3.0 <https://creativecommons.org/licenses/by-sa/3.0>, via Wikimedia Commons");
  credits.emplace_back("https://commons.wikimedia.org/wiki/File:Waltzing-Matilda-_Christina-Macpherson_-Wikipedia.ogg", "BDW82, CC BY-SA 4.0 <https://creativecommons.org/licenses/by-sa/4.0>, via Wikimedia Commons");
  credits.emplace_back("https://opengameart.org/content/giant-spider-32x32", "Spider made by Tuomo Untinen");
  credits.emplace_back("https://opengameart.org/content/100-isometric-bushes", "Hansjörg Malthaner, and link here: http://opengameart.org/users/varkalandar");
}

Credit::Credit(std::string file, std::string author) : file{file}, author{author} {

}


void CreditsScreen::draw() {
  int line{};
  int lines = credits.size()*2 + 5;

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
