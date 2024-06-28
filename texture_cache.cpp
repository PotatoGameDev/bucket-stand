#include "texture_cache.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <ostream>
#include <raylib.h>
#include <string>
#include <utility>

namespace potato_bucket {
TextureCache::TextureCache(){};
TextureCache::~TextureCache(){};

std::shared_ptr<Texture2D> TextureCache::load(std::string path) {
    print();
  auto found = cache.find(path);
  if (found != cache.end()) {
    return found->second;
  }

  Texture2D texture = LoadTexture((path).c_str());
  auto inserted = cache.insert(std::make_pair(path, std::make_shared<Texture2D>(std::move(texture))));

  return inserted.first->second;
}

void TextureCache::unload() {
    for (auto pair : cache) {
      UnloadTexture(*pair.second);
    }
}

void TextureCache::print(std::string pre) {
    std::cout << pre << std::endl;
 for (const auto& pair : cache) {
    std::cout << "Key (texture path): " <<  pair.first 
              << ", Value (Texture2D id): " << pair.second.get()->id
              << std::endl;
  }
}
} // namespace potato_bucket
