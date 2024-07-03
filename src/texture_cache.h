#ifndef POTATO_BUCKET_TEXTURECACHE_H
#define POTATO_BUCKET_TEXTURECACHE_H

#include "raylib.h"
#include <map>
#include <string>
#include <vector>
#include <memory>

namespace potato_bucket {

class TextureCache {
private:
  std::map<std::string, std::shared_ptr<Texture2D>> cache{};

  TextureCache();
  ~TextureCache();

  TextureCache(TextureCache const &);
  void operator=(TextureCache const &);

public:
  static TextureCache &Instance() {
    static TextureCache instance;
    return instance;
  }

  std::shared_ptr<Texture2D> load(std::string);
  void unload();
  void print(std::string = "");
};

} // namespace potato_bucket

#endif
