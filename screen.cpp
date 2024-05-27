#include "screen.h"
#include "world.h"
#include <cstdlib>
#include <raylib.h>

namespace potato_bucket {

// WorldScreen
WorldScreen::WorldScreen(ScreenSettings settings) : world{0, {}} {}

void WorldScreen::update() { world.update(); }

void WorldScreen::draw() { world.draw(); }
} // namespace potato_bucket
