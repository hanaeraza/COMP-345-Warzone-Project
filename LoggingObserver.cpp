#pragma once

#include "LoggingObserver.h"

#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

Subject::Subject(){
  observers = new list<Observer*>();
}
Subject::Subject(const Subject& input){
  this->observers = input.observers;
}

void Subject::attach(Observer* observer){
  observers->push_back(observer);
}

void Subject::detach(Observer* observer){
  observers->remove(observer);
}

void Subject::notify(ILoggable* message){
  for (list<Observer*>::iterator it = observers->begin(); it != observers->end(); ++it)
    (*it)->update(message);
}

void LogObserver::update(ILoggable* message){
  std::ofstream file(logFile, std::ios::app);
  if (file.is_open()) {
      time_t now = time(nullptr);
      file << "Message At: " << now << "\n\t" << message->stringToLog();
      file.close();
  }
  cout << message->stringToLog();
}

ILoggable& ILoggable::operator =(const ILoggable& other){
  return *this;
}

Observer& Observer::operator =(const Observer& other){
  return *this;
}

Subject& Subject::operator =(const Subject& other){
  this->observers = other.observers;
  return *this;
}

LogObserver& LogObserver::operator =(const LogObserver& other){
  this->logFile = other.logFile;
  return *this;
}

LogObserver::LogObserver(string file){
  logFile = const_cast<char*>(file.c_str());
}
LogObserver::LogObserver(char* file){
  logFile = file;
}