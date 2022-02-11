#include "Entities/Strategies/StrategyChangeLevel.h"
#include "Game.h"

void StrategyChangeLevel::performCollisionStrategy(int data) const {
    Game * game = Game::GetInstance();
    game->changeLevel(data);
}
