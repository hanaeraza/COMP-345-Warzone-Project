#pragma once

#include <string>
#include <list>

using namespace std;

class Subject {
public:
  virtual void attach(Observer* observer){
    observers->push_back(observer);
  }
  virtual void detach(Observer* observer){
    observers->remove(observer);
  }
  virtual void notify() = 0;

  list<Observer*>* observers;
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