#pragma once

#include <string>

using namespace std;

class Subject {
public:
  virtual void attach(Observer* observer) = 0;
  virtual void detach(Observer* observer) = 0;
  virtual void notify() = 0;
};

class Observer {
public:
  virtual void update(Subject* subject) = 0;
};

class LogObserver : public Observer {
public:
  void update(Subject* subject) override;
};

class ILoggable {
public:
  virtual string stringToLog() const = 0;
};