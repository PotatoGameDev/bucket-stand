#ifndef POTATO_BUCKET_SCREEN_H
#define POTATO_BUCKET_SCREEN_H

#include "raylib.h"
#include "world.h"

namespace potato_bucket {


struct ScreenSettings {

};

class Screen {
private:
  
public:
  void update() = delete;
  void draw() = delete;
};


class WorldScreen : Screen {
private:
  World world;

public:
  WorldScreen(ScreenSettings = {});
  void update();
  void draw();
};

class MenuScreen : Screen {
private:

public:
  void update();
  void draw();
};

} // namespace potato_bucket

#endif
