#ifndef POTATO_BUCKET_OBJECT_H
#define POTATO_BUCKET_OBJECT_H

#include "anim.h"
#include "raylib.h"
#include <string>
#include <vector>

namespace potato_bucket {

class Object {
private:
public:
  Rectangle box;
  Anim anim;

  Object(float, float, float, float, std::string);
  Object(Rectangle, std::string);

  void update();
  void draw();
};

} // namespace potato_bucket

#endif
