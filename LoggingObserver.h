#pragma once

#include <string>
#include <list>

using namespace std;


// class ConcreteSubject : public Subject{
// public:
// };

class ILoggable {
public:
  virtual string stringToLog() const = 0;

  ILoggable& operator =(const ILoggable& other);
};

class Observer {
public:
  virtual void update(ILoggable* message) = 0;
  virtual void update(string message) = 0;

  Observer& operator =(const Observer& other);
};

class Subject {
public:
  Subject();
  Subject(const Subject& input);
  
  virtual void attach(Observer* observer);
  virtual void detach(Observer* observer);
  virtual void notify(ILoggable* message);
  void notify(string message);

  Subject& operator =(const Subject& other);

protected:
  list<Observer*>* observers;
};

class LogObserver : public Observer {
public:
  LogObserver(string file);
  LogObserver(char* file);
  void update(ILoggable* message) override;
  void update(string message) override;

  LogObserver& operator =(const LogObserver& other);

private:
  string logFile = "log.txt";
};