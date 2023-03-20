#include <iostream>
#include <string>
#include <sstream>
#include "GameEngine.h"
#include "Map.cpp"
#include "Map.h"
using namespace std;

   static int numPlayers = 0; 
   Player * players;

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
    
    string input;
    string command;
    string filename;
    while (true)
    {
        cout << "Enter next command: ";
        getline(cin, input);
        stringstream ss(input);
         ss >> command;
         ss >> filename;
        
        if (command == "loadmap" && !filename.empty())
        {
            MapLoader map = MapLoader(filename);
            game->setState(new MapLoadedState(map));
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

MapLoadedState::MapLoadedState(MapLoader map) : map(map) {}


// Map loaded state
void MapLoadedState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Map loaded state" << endl;
    
    string input;
    string command;
    string command2;
    while (true)
    {
        cout << "Enter next command: ";
        getline(cin, input);
        stringstream ss(input);
         ss >> command;
         ss >> command2;

        if (command == "validatemap" && command2.empty())
        {
            
            if (map.GetMap().Validate() == true) {
            game->setState(new MapValidatedState(map)); }
            else {
                cout << "The map is invalid. Please load a new map." << endl;
            }
            break;
        }
        if (command == "loadmap" && !command2.empty())
        {
            map = MapLoader(command2);
            cout << "New map was loaded" << endl;
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


MapValidatedState::MapValidatedState(MapLoader map) : map(map) {}


// Map validated state
void MapValidatedState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Map validated state" << endl;
    
    string input;
    string command;
    string playername;
    while (true)
    {
        cout << "Enter next command: ";
        getline(cin, input);
        stringstream ss(input);
         ss >> command;
         ss >> playername;
        
        if (command == "addplayer" && !playername.empty())
        {
            numPlayers += 1; 
            cout << numPlayers << endl; 
            game->setState(new PlayersAddedState(map));
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

PlayersAddedState::PlayersAddedState(MapLoader map) : map(map) {}

// Players added state
void PlayersAddedState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Players Added state" << endl;
    
    string input;
    string command;
    string playername;
    while (true)
    {
        cout << "Enter next command: ";
        getline(cin, input);
        stringstream ss(input);
         ss >> command;
         ss >> playername;
        
        if (command == "addplayer" && !playername.empty())
        {
            numPlayers++; 
            cout << numPlayers << endl; 
            cout << "New player added!" << endl;
            break;
        }
        if (command == "gamestart")
        {
            if (numPlayers > 6 || numPlayers < 2) {
                cout << "You need between 2 and 6 players to start!" << endl; 
            }
            else {
            players = new Player[numPlayers];
            game->setState(new ReinforcementsState(map));
            break;
            }
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

ReinforcementsState::ReinforcementsState(MapLoader map) : map(map) {}

// Assign reinforcements state
void ReinforcementsState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Assign reinforcements state" << endl;
    
    vector<Territory> territories = map.GetMap().GetTerritories(); 

    int numTerritories = territories.size(); 
    cout << "numTerritories: " << numTerritories << endl;
    int terrPerPlayer = numTerritories / numPlayers; 
    cout << "territories per player: " << terrPerPlayer << endl; 

    for (int i = 0; i < numPlayers; i++) {
        cout << "Player: " << players[i] << endl; 
        for (int j = 0; j < terrPerPlayer; j++) {
            players[i].territoriesOwned.push_back(territories[j]); 
            cout << "Territory: " << territories[j + (numPlayers * terrPerPlayer)] << endl; 
        }
    }





    string command;
    while (true)
    {
        cout << "Enter next command: ";
        cin >> command;
        if (command == "issueorder")
        {
            game->setState(new IssueOrdersState(map));
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

IssueOrdersState::IssueOrdersState(MapLoader map) : map(map) {}

// Issue orders state
void IssueOrdersState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Issue orders state" << endl;
    
    string command;
    while (true)
    {
        cout << "Enter next command: ";
        cin >> command;
        if (command == "issueorder")
        {
            cout << "New orders issued" << endl;
            break;
        }
        if (command == "endissueorders")
        {
            game->setState(new ExecuteOrdersState(map));
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

ExecuteOrdersState::ExecuteOrdersState(MapLoader map) : map(map) {}

// Execute orders state
void ExecuteOrdersState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Execute orders state" << endl;
    
    string command;
    while (true)
    {
        cout << "Enter next command: ";
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
            game->setState(new ReinforcementsState(map));
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
        cout << "Enter next command: ";
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
 