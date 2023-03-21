#pragma once

#include "GameEngine.h"
// #include "LoggingObserver.h"

#include <iostream>
#include <fstream>
#include <sstream>

int main(){
    GameEngine* game = new GameEngine();
    game->generateLogger("log.txt");
    game->setCommandProcessor(new CommandProcessor());
    while (true){
        game->transition();
    }
    return 0;
}