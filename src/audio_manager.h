#ifndef POTATO_BUCKET_AUDIOMANAGER_H
#define POTATO_BUCKET_AUDIOMANAGER_H

#include "raylib.h"
#include <map>
#include <string>
#include <vector>

namespace potato_bucket {

class AudioMan {
private:
  std::map<std::string, Sound> cache{};

  AudioMan() = default;
  ~AudioMan();

  AudioMan(AudioMan const &);
  void operator=(AudioMan const &);

public:
  static AudioMan &Instance() {
    static AudioMan instance;
    return instance;
  }

  void play(std::string, Vector2 = {0.0f, 0.0f}, Vector2 = {0.0f, 0.0f});
  void unload();
};

} // namespace potato_bucket

#endif
