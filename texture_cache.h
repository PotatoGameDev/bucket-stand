#ifndef POTATO_BUCKET_TEXTURECACHE_H
#define POTATO_BUCKET_TEXTURECACHE_H

#include "raylib.h"
#include <map>
#include <string>
#include <vector>

namespace potato_bucket {

class TextureCache {
private:
  std::map<std::string, Texture2D> cache{};

  TextureCache();
  ~TextureCache();

  TextureCache(TextureCache const &);
  void operator=(TextureCache const &);

public:
  static TextureCache &Instance() {
    static TextureCache instance;
    return instance;
  }

  Texture2D &load(std::string);
  void unload();
};

} // namespace potato_bucket

#endif
