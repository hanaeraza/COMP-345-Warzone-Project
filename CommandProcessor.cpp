#pragma once

#include "CommandProcessor.h"
#include "GameEngine.h"
#include "LoggingObserver.h"

#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <list>

using namespace std;

// class State;

CommandProcessor& CommandProcessor::operator =(const CommandProcessor& other){
  this->commandQueue = other.commandQueue;
  return *this;
}

Command& Command::operator =(const Command& other){
  this->functionName = other.functionName;
  this->parameters = other.parameters;
  this->validIn = other.validIn;
  this->nextState = other.nextState;
  this->effect = other.effect;
  return *this;
}

FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator =(const FileCommandProcessorAdapter& other){
  this->commandQueue = other.commandQueue;
  return *this;
}

ostream& operator<<(ostream& os, const Command& input){
  os << *(input.functionName);
  for (int i = 0; i < input.parameters->size(); i++)
  {
    os << " " << (*(input.parameters))[i];
  }
  os << "\n" << *(input.effect);
  return os;
}

ostream& operator<<(ostream& os, const CommandProcessor& input){
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

ostream& operator<<(ostream& os, const FileCommandProcessorAdapter& input){
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

CommandProcessor::CommandProcessor(){
  this->commandQueue = new queue<Command*>();
}

CommandProcessor::CommandProcessor(const CommandProcessor& other){
  this->commandQueue = other.commandQueue;
}

Command CommandProcessor::getCommand(){
  if (commandQueue->size() <= 0)
    return Command(string(""));

  Command output = *(commandQueue->front());

  return output;
}

void CommandProcessor::saveCommand(Command input){
  notify(this);
  std::ofstream file(logFile, std::ios::app);
  if (file.is_open()) {
      time_t now = time(nullptr);
      file << now << "\n " << input << "\n" << *(input.effect);
      file.close();
  }
}

void CommandProcessor::next(){
  if (commandQueue->size() <= 0)
    return;

  Command last = *(commandQueue->front());
  CommandProcessor::saveCommand(last);
  commandQueue->pop();
}

int CommandProcessor::size(){
  return commandQueue->size();
}

bool CommandProcessor::hasCommand(){
  return commandQueue->size() > 0;
}

bool CommandProcessor::validate(Command input, State* currentState){
  for (int i = 0; i < input.validIn->size(); i++)
  {
    if ((*input.validIn)[i].compare((*currentState).getName()) == 0)
      return true;
  }
  input.saveEffect("Command Invalid In " + (*currentState).getName());
  return false;
}

bool CommandProcessor::validate(Command input, string currentState){
  for (int i = 0; i < input.validIn->size(); i++)
  {
    if ((*input.validIn)[i].compare(currentState) == 0)
      return true;
  }
  input.saveEffect("Command Invalid In " + currentState);
  return false;
}

bool CommandProcessor::validate(State* currentState){
  for (int i = 0; i < (*(commandQueue->front())).validIn->size(); i++)
  {
    if ((*((*(commandQueue->front())).validIn))[i].compare((*currentState).getName()) == 0)
      return true;
  }
  (*(commandQueue->front())).saveEffect("Command Invalid In " + (*currentState).getName());
  return false;
}

bool CommandProcessor::validate(string currentState){
  for (int i = 0; i < (*(commandQueue->front())).validIn->size(); i++)
  {
    if ((*((*(commandQueue->front())).validIn))[i].compare(currentState) == 0)
      return true;
  }
  (*(commandQueue->front())).saveEffect("Command Invalid In " + currentState);
  return false;
}

void CommandProcessor::readCommand(){
  string input;

  cout << "- ";

  getline(cin, input);

  Command* newCommand = new Command(input);

  commandQueue->push(newCommand);
}

string CommandProcessor::stringToLog() const {
  stringstream stream;
  string output;
  stream << *this;
  output = stream.str();
  return output;
}

string Command::stringToLog() const {
  stringstream stream;
  string output;
  stream << *this;
  output = stream.str();
  return output;
}

Command::Command(const Command& other){
  functionName = new string(*(other.functionName));
  parameters = new vector<string>(*(other.parameters));
  validIn = new vector<string>(*(other.validIn));
  nextState = new vector<string>(*(other.nextState));
  effect = new string(*(other.effect));
}

Command::Command(const string input){
  istringstream iss(input);
  vector<string> splitBySpace;
  string token;
  while (iss >> token) {
    splitBySpace.push_back(token);
  }

  functionName = new string(splitBySpace[0]);

  parameters = new vector<string>();
  validIn = new vector<string>();
  nextState = new vector<string>();
  effect = new string();

  for (int i = 1; i < splitBySpace.size(); i++)
  {
    (*parameters).push_back(splitBySpace[i]);
  }
  
  if (splitBySpace[0].compare("loadmap") == 0)
  {
    string v1("start");
    string v2("maploaded");
    string t1("maploaded");
    validIn->push_back(v1);
    validIn->push_back(v2);
    nextState->push_back(t1);
  }
  else if (splitBySpace[0].compare("validatemap") == 0)
  {
    string v1("maploaded");
    string t1("mapvalidated");
    validIn->push_back(v1);
    nextState->push_back(t1);
  }
  else if (splitBySpace[0].compare("addplayer") == 0)
  {
    string v1("mapvalidated");
    string v2("playersadded");
    string t1("mapvalidated");
    validIn->push_back(v1);
    validIn->push_back(v2);
    nextState->push_back(t1);
  }
  else if (splitBySpace[0].compare("gamestart") == 0)
  {
    string v1("playersadded");
    string t1("assignreinforcement");
    validIn->push_back(v1);
    nextState->push_back(t1);
  }
  else if (splitBySpace[0].compare("replay") == 0)
  {
    string v1("win");
    string t1("start");
    validIn->push_back(v1);
    nextState->push_back(t1);
  }
  else if (splitBySpace[0].compare("quit") == 0)
  {
    string v1("win");
    string t1("exit program");
    validIn->push_back(v1);
    nextState->push_back(t1);
  }
}

void Command::saveEffect(string input){
  notify(this);
  *effect += input + "\n";
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string file){
  ifstream inputFile(file);

  string lastLine;

  bool record = false;

  this->commandQueue = new queue<Command*>();

  while (getline(inputFile, lastLine))
  {
    (*commandQueue).push(new Command(lastLine));
  }
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other){
  this->commandQueue = other.commandQueue;
}