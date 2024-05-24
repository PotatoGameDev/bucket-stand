#ifndef POTATO_BUCKET_WORLD_H
#define POTATO_BUCKET_WORLD_H

#include <vector>
#include "raylib.h"
#include "player.h"

namespace potato_bucket {

class World {
private:
    Player player;

public:
  World(Player);
};

}

#endif
