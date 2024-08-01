#ifndef POTATO_BUCKET_GAMESTATE_H
#define POTATO_BUCKET_GAMESTATE_H

#include <bitset>
namespace potato_bucket {

enum Perk {
  // Postive perks:
  CHAIN_REACTION,    // Player bullets split into 2 smaller ones when they hit
                     // enemy bullets
  BULLET_CONVERSION, // Player bullets turn enemy bullets into player bullets
  // Negative perks:
  ONLY_BACKWARDS, // Player can only walk backwards

  PERKS_COUNT
};

class GameState {
private:
  std::bitset<PERKS_COUNT> perks;

public:
  bool getPerk(Perk);
  void setPerk(Perk, bool);
  void flipPerk(Perk);
  int getPerksUsed();
};
} // namespace potato_bucket

#endif
