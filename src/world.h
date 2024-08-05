#ifndef POTATO_BUCKET_WORLD_H
#define POTATO_BUCKET_WORLD_H

#include "bullet.h"
#include "gamestate.h"
#include "object.h"
#include "player.h"
#include "raylib.h"
#include <memory>
#include <string>
#include <vector>

namespace potato_bucket {

class Enemy;

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
  bool intro{false};
};

class World {
private:
  std::shared_ptr<Texture2D> backgnd;
  std::vector<Object> objects{};
  std::vector<Bullet> bullets{};
  std::vector<std::unique_ptr<Enemy>> enemies{};
  int frameNo{};
  const std::shared_ptr<GameState> &gameState;

public:
  Player player;
  Camera2D camera;
  WorldSettings settings;

  ~World() = default;
  World(unsigned int, const std::shared_ptr<GameState> &);

  void addBullet(Vector2, Vector2, float, bool);
  WorldFlow update();
  void draw();
  WorldResult result();
};

void PrintRectum(const Rectangle &);
void PrintVectorum(const Vector2 &);

} // namespace potato_bucket

#endif
