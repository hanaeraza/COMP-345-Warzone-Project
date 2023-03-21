#pragma once

#include "GameEngine.h"
// #include "LoggingObserver.h"
#include "CommandProcessor.h"

#include <iostream>
#include <fstream>
#include <sstream>

int main(){
    GameEngine* game = new GameEngine();
    game->generateLogger("log.txt");
    char input;
    std::cout << "Enter a to read commands from file: ";
    std::cin >> input;
    if (input == 'a')
    {
      game->setCommandProcessor(new CommandProcessor());
    }
    else
    {
      game->setCommandProcessor(new FileCommandProcessorAdapter("commands1.txt"));
    }
    while (true){
        game->transition();
    }
    return 0;
}