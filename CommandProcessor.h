#pragma once

#include "GameEngine.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

class Command
{
public:
  Command(const string input);
  Command(const Command& other);
  ~Command() = default;

  void saveEffect(string effect);

  string* functionName;
  vector<string>* parameters;
  vector<string>* validIn;
  vector<string>* nextState;
  string* effect;

  friend ostream& operator<<(ostream& os, const Command& input){
		os << *(input.functionName);
    for (int i = 0; i < input.parameters->size(); i++)
    {
      os << " " << (*(input.parameters))[i];
    }
    os << "\n" << *(input.effect);
    return os;
	}
};
class CommandProcessor
{
public:
  Command getCommand();
  void saveCommand(Command input);
  void next();
  static bool validate(Command input, State* currentState);
  static bool validate(Command input, string currentState);
  bool validate(State* currentState);
  bool validate(string currentState);
  void readCommand();

  CommandProcessor();
  ~CommandProcessor() = default;

  const char* logFile = "CommandLog.txt";
protected:
  // GameEngine* engine;
  queue<Command*>* commandQueue;
};
class FileCommandProcessorAdapter : CommandProcessor
{
public:
  FileCommandProcessorAdapter(string file);
};