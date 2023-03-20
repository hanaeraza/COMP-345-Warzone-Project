#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <iostream>
#include "Map.cpp"

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
    MapLoadedState(MapLoader map);
    void update(GameEngine *game);
    string getName();
private:
    MapLoader map;
};

class MapValidatedState : public State
{
public:
    MapValidatedState(MapLoader map);
    void update(GameEngine *game);
    string getName();
private:
    MapLoader map;
};

class PlayersAddedState : public State
{
public:
    PlayersAddedState(); 
    PlayersAddedState(MapLoader map);
    void update(GameEngine *game);
    string getName();
private:
    MapLoader map;
};

class ReinforcementsState : public State
{
public:
    ReinforcementsState();
    ReinforcementsState(MapLoader map);
    void update(GameEngine *game);
    string getName();
private:
    MapLoader map;
};

class IssueOrdersState : public State
{
public:
    IssueOrdersState(); 
    IssueOrdersState(MapLoader map);
    void update(GameEngine *game);
    string getName();
private:
    MapLoader map;
};

class ExecuteOrdersState : public State
{
public:
    ExecuteOrdersState(); 
    ExecuteOrdersState(MapLoader map);
    void update(GameEngine *game);
    string getName();
private:
    MapLoader map;
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