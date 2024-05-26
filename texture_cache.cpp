#include "texture_cache.h"
#include <algorithm>
#include <iostream>
#include <raylib.h>
#include <string>
#include <utility>

namespace potato_bucket {
TextureCache::TextureCache(){};
TextureCache::~TextureCache(){};

Texture2D &TextureCache::load(std::string path) {
  auto found = cache.find(path);
  if (found != cache.end()) {
    return found->second;
  }

  Texture2D texture = LoadTexture(("ass/" + path).c_str());
  auto inserted = cache.insert(std::make_pair(path, std::move(texture)));

  return inserted.first->second;
}

void TextureCache::unload() {}
} // namespace potato_bucket
