#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <iostream>
#include "Map.h"
#include "LoggingObserver.h"
#include "CommandProcessor.h"

using namespace std;

class CommandProcessor;
class State;

class GameEngine : public Subject, public ILoggable
{
public:
    GameEngine();
    GameEngine(const GameEngine& s);
    
    void setState(State *state);
    void transition();
    string getCurrentState();

    string stringToLog() const override;

    void setCommandProcessor(CommandProcessor *commandProcessor);
    CommandProcessor getCommandProcessor();
    void setMapLoader(MapLoader *input);
    MapLoader getMapLoader();
    LogObserver* getInnerEngineLogger();

    void generateLogger(string file);

    friend ostream& operator<<(ostream& os, const GameEngine& input);
    
    void mainGameLoop(GameEngine *game);
private:
    State* currentState;
    CommandProcessor* commandProcessor;
    LogObserver* innerEngineLogger;
    MapLoader* mapLoader;
};

// Abstract class
class State
{
public:
    virtual void transition(GameEngine *game) = 0;
    virtual string getName() = 0; 
};


class StartState : public State
{
public:
    void transition(GameEngine *game);
    string getName();
};

class MapLoadedState : public State
{
public:
   
    void transition(GameEngine *game);
    string getName();

};

class MapValidatedState : public State
{
public:
 
    void transition(GameEngine *game);
    string getName();
};

class PlayersAddedState : public State
{
public:
    
    void transition(GameEngine *game);
    string getName();
   
};

class ReinforcementsState : public State
{
public:
    
    void transition(GameEngine *game);
    string getName();
    void reinforcementPhase(Player player);

};

class IssueOrdersState : public State
{
public:
    
    void transition(GameEngine *game);
    string getName();
    void issueOrdersPhase(Player player);

};

class ExecuteOrdersState : public State
{
public:
    
    void transition(GameEngine *game);
    string getName();
    void executeOrdersPhase(Player player);

};


class WinState : public State
{
public:
    void transition(GameEngine *game);
    string getName();
};

class EndState : public State
{
public:
    void transition(GameEngine *game);
    string getName();
};




#endif
