#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <queue>
#include "GameEngine.h"
#include "Card.h"
//#include "Map.cpp"
#include "Map.h"
using namespace std;

static int numPlayers = 0;
vector<Player> players;
Deck *deck = new Deck();
MapLoader map;

queue<Player> playerQueue;

// Start program in the start state
GameEngine::GameEngine() : currentState(new StartState()) {}

// Function to set next state
void GameEngine::setState(State *state)
{
    currentState = state;
}

void GameEngine::transition()
{
    currentState->transition(this);
}

string GameEngine::getCurrentState()
{
    return currentState->getName();
}

// Start state
void StartState::transition(GameEngine *game)
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
void MapLoadedState::transition(GameEngine *game)
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

            if (map.GetMap().Validate() == true)
            {
                game->setState(new MapValidatedState());
            }
            else
            {
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



// Map validated state
void MapValidatedState::transition(GameEngine *game)
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
            numPlayers++;
            players.push_back(Player(playername));
            cout << numPlayers << endl;
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
void PlayersAddedState::transition(GameEngine *game)
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
            players.push_back(Player(playername));

            cout << numPlayers << endl;
            cout << "New player added!" << endl;
            break;
        }
        if (command == "gamestart")
        {
            if (numPlayers > 6 || numPlayers < 2)
            {
                cout << "You need between 2 and 6 players to start!" << endl;
            }
            else
            {
                cout << "Game starting!" << endl;
                // Fairly distribute all territories to the players. Remainder territories (if total # of territories is odd)
                // are left as neutral territories.
                vector<Territory*> territories = map.GetMap().GetTerritories();

                int numTerritories = territories.size();
                cout << "numTerritories: " << numTerritories << endl;
                int terrPerPlayer = numTerritories / numPlayers;
                cout << "Territories per player: " << terrPerPlayer << endl;

                for (int i = 0; i < numPlayers; i++)
                {
                    cout << "Player: " << players[i].playername << endl;
                    for (int j = 0; j < terrPerPlayer; j++)
                    {
                        players[i].territoriesOwned.push_back(*(territories[j]));
                        cout << "Territory: " << territories[j + (i * terrPerPlayer)]->GetTerritoryName() << endl;
                    }
                }

                // Shuffle order of play of the players randomly
                auto rd = random_device{};
                auto rng = default_random_engine{rd()};
                shuffle(begin(players), end(players), rng);

                cout << "Shuffled players: ";
                for (int i = 0; i < numPlayers; i++)
                {
                    cout << players[i].playername << ", ";
                }

                // Give players 50 initial reinforcements
                cout << endl
                     << "Reinforcements: ";
                for (int i = 0; i < numPlayers; i++)
                {
                    players[i].reinforcementPool = 50;
                    cout << players[i].playername << ": " << players[i].reinforcementPool << endl;
                }

               /*  for (int i = 0; i < numPlayers; i++)
                {
                    for (int j = 0; j < 1; j++)
                    {
                        players[i].cardsOwned.cards[j] = deck->draw();
                    }

                    players[i].cardsOwned.printHand();
                } */

                for (int i = 0; i < numPlayers; i++)
                {
                    playerQueue.push(players[i]);
                }

                game->mainGameLoop(game);
                // game->setState(new ReinforcementsState(map));
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

void GameEngine::mainGameLoop(GameEngine *game)
{
    while (true)
    {
        cout << "-----------------------------------" << endl;
        cout << "Main game loop" << endl;
        cout << "Current player: " << playerQueue.front().playername << endl;
        game->setState(new ReinforcementsState());
        cout << "Reinforcements: " << playerQueue.front().reinforcementPool << endl;
        game->setState(new IssueOrdersState());

        game->setState(new ExecuteOrdersState());

        Player p = playerQueue.front();
        playerQueue.pop();
        playerQueue.push(p);
    }
}


// Assign reinforcements state
void ReinforcementsState::transition(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Assign reinforcements state" << endl;

    reinforcementPhase(playerQueue.front());
    string command;
    while (true)
    {
        cout << "Enter next command: ";
        cin >> command;
        if (command == "issueorder")
        {
            // game->setState(new IssueOrdersState(map));
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}

void ReinforcementsState::reinforcementPhase(Player player)
{
    for (int i = 0; i < numPlayers; i++)
    {
        cout << "Player " << (i + 1) << " number of reinforcements: ";
        int numTerritoriesOwned = player.territoriesOwned.size();
        int numReinforcementsFromTerritories = floor(numTerritoriesOwned / 3);
        cout << "Number of Reinforcements from Territories: " << numReinforcementsFromTerritories << endl;
        // check for continent control here
        int numReinforcementsFromContinents = 0;
        vector<string> continentsOwned = map.GetMap().GetContinentsOwnedBy(player);

        for (int i = 0; i < continentsOwned.size(); i++)
        {
            numReinforcementsFromContinents += map.GetMap().GetContinentBonus(continentsOwned[i]);
        }

        cout << "Number of Reinforcements from Continents: " << numReinforcementsFromContinents << endl;
        int totalReinforcements = numReinforcementsFromTerritories + numReinforcementsFromContinents;
        if (totalReinforcements < 3)
        {
            totalReinforcements = 3;
        }
        cout << "Total Reinforcements for player " << player.playername << ": " << totalReinforcements << " armies " << endl;
        player.reinforcementPool += totalReinforcements;
    }
}

string ReinforcementsState::getName()
{
    return "ReinforcementsState";
}



// Issue orders state
void IssueOrdersState::transition(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Issue orders state" << endl;

    issueOrdersPhase(playerQueue.front());

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
            // game->setState(new ExecuteOrdersState(map));
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}

void IssueOrdersState::issueOrdersPhase(Player player)
{
    player.issueOrder(map);
}

string IssueOrdersState::getName()
{
    return "IssueOrdersState";
}



// Execute orders state
void ExecuteOrdersState::transition(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Execute orders state" << endl;

    executeOrdersPhase(playerQueue.front());

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
            game->setState(new ReinforcementsState());
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}
void ExecuteOrdersState::executeOrdersPhase(Player player)
{
}
string ExecuteOrdersState::getName()
{
    return "ExecuteOrdersState";
}

// Win state
void WinState::transition(GameEngine *game)
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
void EndState::transition(GameEngine *game)
{
    // end
}

string EndState::getName()
{
    return "EndState";
}

/* void GameEngine::mainGameLoop(){
    reinforcementPhase();
} */
