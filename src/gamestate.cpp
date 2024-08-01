#include "gamestate.h"

namespace potato_bucket {
bool GameState::getPerk(Perk perk) { return perks[perk]; }
void GameState::setPerk(Perk perk, bool val) { perks[perk] = val; }
void GameState::flipPerk(Perk perk) { perks.flip(perk); }
int GameState::getPerksUsed() { return perks.count(); }
} // namespace potato_bucket
