#include "object.h"
#include "anim.h"
#include <raylib.h>
#include <iostream>
#include <string>

namespace potato_bucket {
Object::Object(float x, float y, float w, float h, std::string animFilename) : Object(Rectangle{x, y, w, h}, animFilename) {}
Object::Object(Rectangle r, std::string animFilename) : box{r}, anim(animFilename, 1, r.x, r.y, 256.0, 256.0) {}

void Object::update() {
    anim.update();
}

void Object::draw() {
  //DrawRectangleRec(box, GetColor(0xFFFFFFFF));
  anim.draw(Vector2{box.x, box.y});
}

void Object::unload() { anim.unload(); }

} // namespace potato_bucket
