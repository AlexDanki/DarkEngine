
#include <iostream>
#include "./core/Engine.h"
#include "./Game/Game.h" 
#include "./game/DarkGame/DarkGame.h"

int main()
{
    DarkGame game;
    game.init();
    game.run();
    game.shutdown();
    return 0;
}