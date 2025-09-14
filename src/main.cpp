
#include <iostream>
#include "./core/Engine.h"
#include "./Game/Game.h" 

int main()
{
    Game game;
    game.init();
    game.run();
    game.shutdown();
    return 0;
}