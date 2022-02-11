#include "Game.h"

int main() {

    Game * game = Game::GetInstance(); //Creating a game singleton.


    while (game->isRunning())
    {
        game->render();
        game->update();

    }

    return 0;
}