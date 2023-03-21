#pragma once

#include "GameEngine.h"
#include "LoggingObserver.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

class Command : public ILoggable, public Subject
{
public:
  Command(const string input);
  Command(const Command& other);
  ~Command() = default;

  void saveEffect(string effect);

  string stringToLog() const override;

  friend ostream& operator<<(ostream& os, const Command& input){
		os << *(input.functionName);
    for (int i = 0; i < input.parameters->size(); i++)
    {
      os << " " << (*(input.parameters))[i];
    }
    os << "\n" << *(input.effect);
    return os;
	}
  
  string* functionName;
  vector<string>* parameters;
  vector<string>* validIn;
  vector<string>* nextState;
  string* effect;
};
class CommandProcessor  : public ILoggable
{
public:
  Command getCommand();
  void saveCommand(Command input);
  void next();
  static bool validate(Command input, State* currentState);
  static bool validate(Command input, string currentState);
  bool validate(State* currentState);
  bool validate(string currentState);
  bool hasCommand();
  void readCommand();

  string stringToLog() const override;

  CommandProcessor();
  ~CommandProcessor() = default;

  const char* logFile = "CommandLog.txt";

  friend ostream& operator<<(ostream& os, const CommandProcessor& input){
    queue<Command*>* readingCommandQueue = new queue<Command*>();

    os << "Commands:\n";

    while (!input.commandQueue->empty())
    {
      readingCommandQueue->push(input.commandQueue->front());
      os << "\t" << *(input.commandQueue->front()) << "\n";
      input.commandQueue->pop();
    }

    while (!readingCommandQueue->empty())
    {
      input.commandQueue->push(readingCommandQueue->front());
      readingCommandQueue->pop();
    }

    delete readingCommandQueue;
    return os;
	}
protected:
  // GameEngine* engine;
  queue<Command*>* commandQueue;
};
class FileCommandProcessorAdapter : CommandProcessor
{
public:
  FileCommandProcessorAdapter(string file);

  friend ostream& operator<<(ostream& os, const FileCommandProcessorAdapter& input){
    queue<Command*>* readingCommandQueue = new queue<Command*>();

    os << "Commands:\n";

    while (!input.commandQueue->empty())
    {
      readingCommandQueue->push(input.commandQueue->front());
      os << "\t" << *(input.commandQueue->front()) << "\n";
      input.commandQueue->pop();
    }

    while (!readingCommandQueue->empty())
    {
      input.commandQueue->push(readingCommandQueue->front());
      readingCommandQueue->pop();
    }

    delete readingCommandQueue;
    return os;
	}
};