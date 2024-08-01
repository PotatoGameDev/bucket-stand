#include "gamestate.h"

namespace potato_bucket {

bool GameState::getPerk(Perk perk) { return perks[perk]; }
void GameState::setPerk(Perk perk, bool val) { perks[perk] = val; }
void GameState::flipPerk(Perk perk) {
  bool perkIsSelected = perks[perk];
  bool isPositivePerk = perk % 2 == 0;
  bool hasPerkPoints = getAvailablePerkPoints() > 0;

  if (isPositivePerk && (hasPerkPoints || perkIsSelected) ||
      !isPositivePerk && (hasPerkPoints || !perkIsSelected)) {
    perks.flip(perk);
  }
}
int GameState::getAvailablePerkPoints() {
  // Left perks (even ones) = positive.
  // Right ones (odd) = negative
  int count = gainedPerkPoints;
  for (int i = 0; i < PERKS_COUNT; i++) {
    if (!perks[i])
      continue;
    if (i % 2 == 0) {
      count--;
    } else {
      count++;
    }
  }

  return count;
}
} // namespace potato_bucket
