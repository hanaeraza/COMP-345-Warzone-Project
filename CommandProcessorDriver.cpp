#pragma once

#include "CommandProcessor.h"

#include <iostream>
#include <fstream>
#include <sstream>

int main(){
  CommandProcessor textCommandProcessor;

  textCommandProcessor.readCommand();
  textCommandProcessor.readCommand();
  textCommandProcessor.readCommand();

  string state;

  std::cout << "What state are we in?";

 getline(cin, state);

  std::cout << "Command Valid: " << CommandProcessor::validate(textCommandProcessor.getCommand(), state);

  std::cout << "Saving Command: " << textCommandProcessor.getCommand();

  textCommandProcessor.saveCommand(textCommandProcessor.getCommand());

  std::cout << "CommandProcessor: " << textCommandProcessor;

  std::cout << "CommandProcessor Again: " << textCommandProcessor;

  FileCommandProcessorAdapter fileCommandProcessor("Commands.txt");

  std::cout << "FileCommandProcessor: " << fileCommandProcessor;

}