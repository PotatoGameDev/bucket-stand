#ifndef POTATO_BUCKET_GUI_H
#define POTATO_BUCKET_GUI_H

#include "raylib.h"
#include "screenflow.h"
#include <raymath.h>
#include <string>

namespace potato_bucket {

// ======================================================================

class Button {
private:
protected:
  int fontSize{20};

public:
  virtual ~Button() = default;
  Button(Vector2, std::string, ScreenFlow);

  Vector2 positionPercent;
  std::string text;
  int textWidth;
  Color fontColor{WHITE};
  ScreenFlow action;
  Rectangle box;
  bool selected{false};

  Button *left = nullptr;
  Button *right = nullptr;
  Button *up = nullptr;
  Button *down = nullptr;

  Button *update();
  bool pressed();
  virtual void draw();

  void setFontSize(int);

  virtual ScreenFlow doAction();
};

class CheckButton : public Button {
private:
  bool checked{false};
  std::string checkedText;
  std::string uncheckedText;

public:
  CheckButton(Vector2, std::string, std::string);
  ScreenFlow doAction();
};

class PerkButton : public Button {
private:
  bool checked{false};

public:
  std::string description;
  int descriptionWidth;

  PerkButton(Vector2, float, std::string, std::string);
  ScreenFlow doAction();
  void draw();
};

} // namespace potato_bucket

#endif
