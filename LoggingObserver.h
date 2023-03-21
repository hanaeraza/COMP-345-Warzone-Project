#pragma once

#include <string>
#include <list>

using namespace std;

class Subject {
public:
  virtual void attach(Observer* observer);
  virtual void detach(Observer* observer);
  virtual void notify(ILoggable* message);
protected:
  list<Observer*>* observers;
};

// class ConcreteSubject : public Subject{
// public:
// };

class Observer {
public:
  virtual void update(ILoggable* message) = 0;
};

class LogObserver : public Observer {
public:
  LogObserver(string file);
  void update(ILoggable* message) override;
private:
  char* logFile = "log.txt";
};

class ILoggable {
public:
  virtual string stringToLog() const = 0;
};