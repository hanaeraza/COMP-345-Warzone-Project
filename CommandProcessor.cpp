#pragma once

#include "CommandProcessor.h"
#include "GameEngine.h"

#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;


CommandProcessor::CommandProcessor(){
  this->commandQueue = new queue<Command*>();
}

Command CommandProcessor::getCommand(){
  if (commandQueue->size() <= 0)
    return nullptr;

  Command output = *(commandQueue->front());
}

void CommandProcessor::saveCommand(Command input){
  std::ofstream file(logFile, std::ios::app);
  if (file.is_open()) {
      time_t now = std::time(nullptr);
      file << now << " " << input << "\n " << *(input.effect);
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

bool CommandProcessor::validate(Command input, State* currentState){
  for (int i = 0; i < input.validIn->size(); i++)
  {
    if ((*input.validIn)[i].compare((*currentState).getName()) == 0)
      return true;
  }
  input.saveEffect("Command Invalid In " + (*currentState).getName());
  return false;
}

void CommandProcessor::readCommand(){
  string input;

  cout << "- ";

  getline(cin, input);

  Command* newCommand = new Command(input);

  commandQueue->push(newCommand);
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