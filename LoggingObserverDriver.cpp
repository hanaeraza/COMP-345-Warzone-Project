#pragma once

#include "GameEngine.h"
// #include "LoggingObserver.h"
#include "CommandProcessor.h"
#include "Orders.h"

#include <iostream>
#include <fstream>
#include <sstream>

int bytesAllocated = 0;
int bytesDeallocated = 0;
int timesAllocated = 0;
int timesDeallocated = 0;

void * operator new(size_t size)
{
  timesAllocated++;
  bytesAllocated += size;
  return malloc(size);
}

void operator delete(void * ptr, size_t size)
{
  timesDeallocated++;
  bytesDeallocated += size;
  free(ptr);
}

int main(){ // tournamentCommand.txt
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