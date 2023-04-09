#pragma once

#include "GameEngine.h"
// #include "LoggingObserver.h"
#include "CommandProcessor.h"
#include "Orders.h"

#include <iostream>
#include <fstream>
#include <sstream>

int main(){
  GameEngine* game = new GameEngine();
  game->generateLogger("log.txt");
  std::string input;
  std::cout << "Enter file or type none: ";
  std::getline(std::cin, input);
  if (input == "none")
  {
    game->setCommandProcessor(new CommandProcessor());
  }
  else
  {
    game->setCommandProcessor(new FileCommandProcessorAdapter(input));
  }
  while (true){
      game->update();
  }
  return 0;
}