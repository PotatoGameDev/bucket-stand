#include "gui.h"
#include "gamestate.h"
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
  if (selected) {
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
  }

  bool newSelected = CheckCollisionPointRec(GetMousePosition(), box);
  if (newSelected) {
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

  setFontSize(fontSize);

  return action;
}

PerkButton::PerkButton(Perk perk, Vector2 positionPercent, float widthPercent,
                       std::string name, std::string description,
                       const std::shared_ptr<GameState> &gameState)
    : Button(positionPercent, name, ScreenFlow::None), gameState{gameState} {

  box = {GetScreenWidth() * positionPercent.x,
         GetScreenHeight() * positionPercent.y, GetScreenWidth() * widthPercent,
         static_cast<float>(this->fontSize + 20)};
  this->description = description;
  this->descriptionWidth = MeasureText(description.c_str(), this->fontSize);
}

ScreenFlow PerkButton::doAction() {
  checked = !checked;

  gameState->setPerk(perk, checked);

  return action;
}

void PerkButton::draw() {
  DrawRectangleLinesEx(box, 2, fontColor);

  float spacer = 1.0f;
  float tickBoxWidth = box.height - spacer * 2;
  Rectangle tickBox{box.x + spacer, box.y + spacer, tickBoxWidth, tickBoxWidth};
  DrawRectangleLinesEx(tickBox, 2, fontColor);

  if (this->selected) {
    DrawRectangleLinesEx(tickBox, 5, fontColor);
    DrawRectangleLinesEx(box, 5, fontColor);
  }

  DrawText(text.c_str(), box.x + box.width / 2 - textWidth / 2.0,
           box.y + box.height / 2 - fontSize / 2.0, fontSize, fontColor);

  if (checked) {
    DrawLineEx(
        {box.x, box.y + static_cast<float>(tickBoxWidth / 2.0)},
        {box.x + static_cast<float>(tickBoxWidth / 2.0), box.y + tickBoxWidth},
        3, RED);
    DrawLineEx(
        {box.x + static_cast<float>(tickBoxWidth / 2.0), box.y + tickBoxWidth},
        {box.x + tickBoxWidth, box.y}, 3, RED);
  }

  if (this->up != nullptr) {
    DrawLineEx({box.x + 20, box.y + 20}, {up->box.x, up->box.y}, 2, GREEN);
  }
  if (this->down != nullptr) {
    DrawLineEx({box.x + 20, box.y + 20}, {down->box.x, down->box.y}, 2, RED);
  }
  if (this->left != nullptr) {
    DrawLineEx({box.x + 20, box.y + 20}, {left->box.x, left->box.y}, 2, BLUE);
  }
  if (this->right != nullptr) {
    DrawLineEx({box.x + 20, box.y + 20}, {right->box.x, right->box.y}, 2,
               YELLOW);
  }
}

} // namespace potato_bucket
