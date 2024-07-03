#ifndef POTATO_BUCKET_MATILDAS_H
#define POTATO_BUCKET_MATILDAS_H

#include "raylib.h"
#include <map>
#include <string>
#include <vector>

namespace potato_bucket {

class Matildas {
private:
  std::vector<Music> cache{};

  Matildas();
  ~Matildas();

  Matildas(Matildas const &);
  void operator=(Matildas const &);

  int current{-1};

public:
  static Matildas &Instance() {
    static Matildas instance;
    return instance;
  }

  void giveMeNextOne();
  void unload();
  void update();
};

} // namespace potato_bucket

#endif
