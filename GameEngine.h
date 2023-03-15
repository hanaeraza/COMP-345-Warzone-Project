#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <iostream>
//#include "Player.cpp"

using namespace std;

class State;

class GameEngine
{
public:
    GameEngine();
    GameEngine(const GameEngine& s);
    
    void setState(State *state);
    void update();
    string getCurrentState();
    
private:
    State* currentState;
    //Player* players[] ;
    
};

// Abstract class
class State
{
public:
    virtual void update(GameEngine *game) = 0;
    virtual string getName() = 0; 
};


class StartState : public State
{
public:
    void update(GameEngine *game);
    string getName();
};

class MapLoadedState : public State
{
public:
    void update(GameEngine *game);
    string getName();
};

class MapValidatedState : public State
{
public:
    void update(GameEngine *game);
    string getName();
};

class PlayersAddedState : public State
{
public:
    void update(GameEngine *game);
    string getName();
};

class ReinforcementsState : public State
{
public:
    void update(GameEngine *game);
    void reinforcementPhase();
    string getName();
};

class IssueOrdersState : public State
{
public:
    void update(GameEngine *game);
    void issueOrdersPhase();
    string getName();
};

class ExecuteOrdersState : public State
{
public:
    void update(GameEngine *game);
    void executeOrdersPhase();
    string getName();
};


class WinState : public State
{
public:
    void update(GameEngine *game);
    string getName();
};

class EndState : public State
{
public:
    void update(GameEngine *game);
    string getName();
};





#endif