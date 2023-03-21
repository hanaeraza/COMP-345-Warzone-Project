#pragma once

#include <string>

using namespace std;

class Subject {
public:
  virtual void attach(Observer* observer) = 0;
  virtual void detach(Observer* observer) = 0;
  virtual void notify() = 0;
};

class ConcreteSubject : public Subject{
public:
};

class Observer {
public:
  virtual void update() = 0;
};

class LogObserver : public Observer {
public:
  LogObserver(string file);
  void update() override;

  string file;
};

class ILoggable {
public:
  virtual string stringToLog() const = 0;
};