
#include "gui.h"
#include "screenflow.h"
#include <raylib.h>
#include <string>
#include <sys/select.h>

namespace potato_bucket {

Button::Button(Vector2 positionPercent, std::string text, ScreenFlow action)
    : positionPercent{positionPercent}, text{text}, action{action} {
  setFontSize(fontSize);
}

Button *Button::update() {
  if (IsKeyPressed(KEY_DOWN)) {
    return down;
  }
  if (IsKeyPressed(KEY_UP)) {
    return up;
  }
  if (IsKeyPressed(KEY_LEFT)) {
    return left;
  }
  if (IsKeyPressed(KEY_RIGHT)) {
    return right;
  }

  bool newSelected = CheckCollisionPointRec(GetMousePosition(), box);
  if (newSelected != selected) {
    return this;
  }

  return nullptr;
}

bool Button::pressed() {
  return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
         CheckCollisionPointRec(GetMousePosition(), box);
}

void Button::draw() {
  if (selected) {
    DrawRectangleLinesEx(box, 2, fontColor);
  }

  DrawText(text.c_str(),
           (GetScreenWidth() * positionPercent.x -
            static_cast<float>(textWidth) / 2),
           GetScreenHeight() * positionPercent.y, fontSize, fontColor);
}

void Button::setFontSize(int fontSize) {
  this->fontSize = fontSize;
  textWidth = MeasureText(text.c_str(), this->fontSize);
  box = {(GetScreenWidth() * positionPercent.x -
          static_cast<float>(textWidth) / 2) -
             10,
         GetScreenHeight() * positionPercent.y - 10,
         static_cast<float>(textWidth) + 20,
         static_cast<float>(this->fontSize) + 20};
}

ScreenFlow Button::doAction() { return action; }

CheckButton::CheckButton(Vector2 positionPercent, std::string uncheckedText,
                         std::string checkedText)
    : Button(positionPercent, uncheckedText, ScreenFlow::None),
      checkedText{checkedText}, uncheckedText{uncheckedText} {};

ScreenFlow CheckButton::doAction() {
  checked = !checked;

  if (checked) {
    text = checkedText;
    SetMasterVolume(0.0f);
  } else {
    text = uncheckedText;
    SetMasterVolume(1.0f);
  }

  return action;
}

} // namespace potato_bucket
