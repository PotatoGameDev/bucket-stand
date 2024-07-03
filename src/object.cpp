#include "object.h"
#include "anim.h"
#include <iostream>
#include <raylib.h>
#include <string>

namespace potato_bucket {
Object::Object(float x, float y, std::string animFilename)
    : Object({x, y}, animFilename) {}
Object::Object(Vector2 pos, std::string animFilename)
    : box{pos.x, pos.y, 0.0f, 0.0f}, anim(animFilename, 1) {

  box.width = anim.width;
  box.height = anim.height;
}

void Object::update() { anim.update(); }

void Object::draw() { anim.draw(Vector2{box.x, box.y}, box); }

} // namespace potato_bucket
