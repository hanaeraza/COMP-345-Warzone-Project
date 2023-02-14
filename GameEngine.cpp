#include <iostream>
#include <string>
#include "GameEngine.h"
using namespace std;

// Start program in the start state
GameEngine::GameEngine() : currentState(new StartState()) {}

// Function to set next state
void GameEngine::setState(State *state)
{
    currentState = state;
}

void GameEngine::update()
{
    currentState->update(this);
}

string GameEngine::getCurrentState()
{
    return currentState->getName();
}

// Start state
void StartState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Start state." << endl;
    
    string command;
    while (true)
    {
        cout << "Enter next state: ";
        cin >> command;
        if (command == "loadmap")
        {
            game->setState(new MapLoadedState());
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}

string StartState::getName()
{
    return "StartState";
}

// Map loaded state
void MapLoadedState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Map loaded state" << endl;
    
    string command;
    while (true)
    {
        cout << "Enter next state: ";
        cin >> command;
        if (command == "validatemap")
        {
            game->setState(new MapValidatedState());
            break;
        }
        if (command == "loadmap")
        {
            cout << "Map was reloaded" << endl;
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}

string MapLoadedState::getName()
{
    return "MapLoadedState";
}

// Map validated state
void MapValidatedState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Map validated state" << endl;
    
    string command;
    while (true)
    {
        cout << "Enter next state: ";
        cin >> command;
        if (command == "addplayer")
        {
            game->setState(new PlayersAddedState());
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}

string MapValidatedState::getName()
{
    return "MapValidatedState";
}

// Players added state
void PlayersAddedState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Players Added state" << endl;
    
    string command;
    while (true)
    {
        cout << "Enter next state: ";
        cin >> command;
        if (command == "addplayer")
        {
            cout << "Another player added" << endl;
            break;
        }
        if (command == "assigncountries")
        {
            game->setState(new ReinforcementsState());
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}

string PlayersAddedState::getName()
{
    return "PlayersAddedState";
}

// Assign reinforcements state
void ReinforcementsState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Assign reinforcements state" << endl;
    
    string command;
    while (true)
    {
        cout << "Enter next state: ";
        cin >> command;
        if (command == "issueorder")
        {
            game->setState(new IssueOrdersState());
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}

string ReinforcementsState::getName()
{
    return "ReinforcementsState";
}

// Issue orders state
void IssueOrdersState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Issue orders state" << endl;
    
    string command;
    while (true)
    {
        cout << "Enter next state: ";
        cin >> command;
        if (command == "issueorder")
        {
            cout << "New orders issued" << endl;
            break;
        }
        if (command == "endissueorders")
        {
            game->setState(new ExecuteOrdersState());
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}

string IssueOrdersState::getName()
{
    return "IssueOrdersState";
}

// Execute orders state
void ExecuteOrdersState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Execute orders state" << endl;
    
    string command;
    while (true)
    {
        cout << "Enter next state: ";
        cin >> command;
        if (command == "execorder")
        {
            cout << "More orders executed" << endl;
            break;
        }
        if (command == "win")
        {
            game->setState(new WinState());
            break;
        }
        if (command == "endexecorders")
        {
            game->setState(new ReinforcementsState());
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}

string ExecuteOrdersState::getName()
{
    return "ExecuteOrdersState";
}

// Win state
void WinState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Win state" << endl;
    string command;
    while (true)
    {
        cout << "Enter next state: ";
        cin >> command;
        if (command == "end")
        {

            cout << "-----------------------------------" << endl;

            cout << "You won!" << endl;
            game->setState(new EndState());
            break;
        }
        if (command == "play")
        {
            game->setState(new StartState());
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}

string WinState::getName()
{
    return "WinState";
}

// End state
void EndState::update(GameEngine *game)
{
    // end
}

string EndState::getName()
{
    return "EndState";
}