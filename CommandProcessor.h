#pragma once

// #include "GameEngine.h"
#include "LoggingObserver.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

class State;

class Command : public ILoggable, public Subject
{
public:
  Command(const string input);
  Command(const Command& other);
  ~Command() = default;

  void saveEffect(string effect);

  string stringToLog() const override;
  string asString() const;

  friend ostream& operator<<(ostream& os, const Command& input);

  Command& operator =(const Command& other);
  
  string* functionName;
  vector<string>* parameters;
  vector<string>* validIn;
  vector<string>* nextState;
  string* effect;
};
class CommandProcessor  : public ILoggable, public Subject
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
  int size();
  void clear();

  string stringToLog() const override;

  CommandProcessor();
  CommandProcessor(const CommandProcessor& other);
  ~CommandProcessor() = default;

  const char* logFile = "CommandLog.txt";

  CommandProcessor& operator =(const CommandProcessor& other);

  friend ostream& operator<<(ostream& os, const CommandProcessor& input);
protected:
  // GameEngine* engine;
  queue<Command*>* commandQueue;
};
class FileCommandProcessorAdapter : public CommandProcessor
{
public:
  FileCommandProcessorAdapter(string file);

  FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other);

  FileCommandProcessorAdapter& operator =(const FileCommandProcessorAdapter& other);

  friend ostream& operator<<(ostream& os, const FileCommandProcessorAdapter& input);
};