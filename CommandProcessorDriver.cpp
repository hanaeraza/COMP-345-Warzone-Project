#pragma once

#include "CommandProcessor.h"

#include <iostream>

int main(){
  CommandProcessor textCommandProcessor;

  textCommandProcessor.readCommand();

  std::cout << "Command Valid: " << CommandProcessor::validate(textCommandProcessor.getCommand(), "start");

  std::cout << "Saving Command: " << textCommandProcessor.getCommand();

  textCommandProcessor.saveCommand(textCommandProcessor.getCommand());
}