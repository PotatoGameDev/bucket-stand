#ifndef POTATO_BUCKET_WORLD_H
#define POTATO_BUCKET_WORLD_H

#include "bullet.h"
#include "enemy.h"
#include "object.h"
#include "player.h"
#include "raylib.h"
#include <memory>
#include <string>
#include <vector>

namespace potato_bucket {

enum class WorldFlow { None, Win, Lose };

struct WorldSettings {
    int winCondition{1};
    std::string location;
    std::string nextLocation;

    WorldSettings() = default;
    WorldSettings(int, std::string, std::string);
};

struct WorldResult {
    int killed{};
    bool win{};
    std::string location;
    std::string nextLocation;
    bool intro {false};
};

class World {
private:
  std::shared_ptr<Texture2D> backgnd;
  std::vector<Object> objects{};
  std::vector<Bullet> bullets{};
  std::vector<std::unique_ptr<Enemy>> enemies{};
  int frameNo{};
  WorldSettings settings;

public:
  Player player;
  Camera2D camera;

  World();
  World(unsigned int, WorldSettings settings = {});

  WorldFlow update();
  void draw();
  WorldResult result();
};

void PrintRectum(const Rectangle&);
void PrintVectorum(const Vector2&);

} // namespace potato_bucket

#endif
