#include "matildas.h"
#include <cstdlib>
#include <raylib.h>
#include <raymath.h>

namespace potato_bucket {

Matildas::Matildas() {
  cache.push_back(LoadMusicStream("resources/Waltzing_Matilda.ogg"));
  cache.push_back(LoadMusicStream(
      "resources/Waltzing-Matilda-_Christina-Macpherson_-Wikipedia.ogg"));
}

Matildas::~Matildas() {};

void Matildas::giveMeNextOne() {
  current = rand() % cache.size();

  PlayMusicStream(cache[current]);
}

void Matildas::update() {
  if (current != -1) {
    UpdateMusicStream(cache[current]);
  }
}

void Matildas::unload() {
  for (auto music : cache) {
    UnloadMusicStream(music);
  }
}
} // namespace potato_bucket
