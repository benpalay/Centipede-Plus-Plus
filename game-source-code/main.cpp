#include "Game.h"
/** \file Main.cpp
  \brief  Constructs the game objects and plays the game.
 */
int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    Game game;
    game.playGame();

    return EXIT_SUCCESS;
}

