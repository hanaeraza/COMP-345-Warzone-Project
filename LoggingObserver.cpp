#pragma once

#include "LoggingObserver.h"

#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

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
      time_t now = std::time(nullptr);
      file << "Message At: " << now << "\n\t" << message->stringToLog();
      file.close();
  }
  cout << message->stringToLog();
}

ILoggable& ILoggable::operator =(const ILoggable& other){
  return *this;
}

ILoggable& ILoggable::operator =(const ILoggable& other){
  return *this;
}

ILoggable& ILoggable::operator =(const ILoggable& other){
  return *this;
}

ILoggable& ILoggable::operator =(const ILoggable& other){
  return *this;
}