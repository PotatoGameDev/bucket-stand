#include "texture_cache.h"
#include "logging.h"
#include <memory>
#include <raylib.h>
#include <string>
#include <utility>

namespace potato_bucket {
TextureCache::TextureCache() {};
TextureCache::~TextureCache() {};

std::shared_ptr<Texture2D> TextureCache::load(std::string path) {
  print();
  auto found = cache.find(path);
  if (found != cache.end()) {
    return found->second;
  }

  Texture2D texture = LoadTexture(("resources/" + path).c_str());
  auto inserted = cache.insert(
      std::make_pair(path, std::make_shared<Texture2D>(std::move(texture))));

  return inserted.first->second;
}

void TextureCache::unload() {
  for (auto pair : cache) {
    UnloadTexture(*pair.second);
  }
}

void TextureCache::print(std::string pre) {
  for (const auto &pair : cache) {
    LOG("Key (texture path): ", pair.first,
        ", Value (Texture2D id): ", pair.second.get()->id);
  }
}
} // namespace potato_bucket
