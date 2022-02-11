#include "Entities/Strategies/StrategyDamagePlayer.h"
#include "Game.h"

void StrategyDamagePlayer::performCollisionStrategy(int data) const {
    Game * game = Game::GetInstance();
    game->player->receiveDamage(data);
}
