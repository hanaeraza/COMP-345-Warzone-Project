#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <queue>
#include "GameEngine.h"
#include "Card.h"
// #include "Map.cpp"
#include "Map.h"
#include "PlayerStrategy.h"
using namespace std;

static int numPlayers = 0;
vector<Player> players;
Deck *deck = new Deck();
MapLoader map;

// queue<Player> playerQueue;

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
            map = MapLoader(filename);
            cout << map.GetMap();
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
void MapValidatedState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Map validated state" << endl;

    string input;
    string command;
    string playername;
    string strategy;
    while (true)
    {
        cout << "Enter next command: ";
        getline(cin, input);
        stringstream ss(input);
        ss >> command;
        ss >> playername;
        ss >> strategy;

        if (command == "addplayer" && !playername.empty() && (strategy == "human" || strategy == "aggressive" || strategy == "benevolent" || strategy == "neutral" || strategy == "cheater"))
        {

            numPlayers++;

            players.push_back(Player(playername, strategy));
            // players.push_back(Player(playername));
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
void PlayersAddedState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Players Added state" << endl;

    string input;
    string command;
    string playername;
    string strategy;

    while (true)
    {
        cout << "Enter next command: ";
        getline(cin, input);
        stringstream ss(input);
        ss >> command;
        ss >> playername;
        ss >> strategy;

        if (command == "addplayer" && !playername.empty() && (strategy == "human" || strategy == "aggressive" || strategy == "benevolent" || strategy == "neutral" || strategy == "cheater"))
        {
            numPlayers++;
            players.push_back(Player(playername, strategy));
            // players.push_back(Player(playername));
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

                vector<Territory *> territories = map.GetMap().GetTerritories();

                int numTerritories = territories.size();
                cout << "numTerritories: " << numTerritories << endl;
                int terrPerPlayer = numTerritories / numPlayers;
                cout << "Territories per player: " << terrPerPlayer << endl;

                // Shuffle territories randomly
                auto rd = random_device{};
                auto rng = default_random_engine{rd()};
                shuffle(begin(territories), end(territories), rng);

                for (int i = 0; i < numPlayers; i++)
                {
                    cout << "Player " << players[i].playername << " Territories:" << endl;
                    for (int j = 0; j < terrPerPlayer; j++)
                    {
                        players[i].territoriesOwned.push_back(*(territories[j + (i * terrPerPlayer)]));
                        (territories[j + (i * terrPerPlayer)])->SetOwner(players[i]);
                        cout << territories[j + (i * terrPerPlayer)]->GetTerritoryName() << ",";
                    }
                    cout << endl;
                }

                // Shuffle order of play of the players randomly
                auto rd2 = random_device{};
                auto rng2 = default_random_engine{rd2()};
                shuffle(begin(players), end(players), rng2);

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
                    players[i].reinforcementPool += 50;
                    cout << players[i].playername << ": " << players[i].reinforcementPool << endl;
                }

                cout << "Players cards: " << endl;
                for (int i = 0; i < numPlayers; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        players[i].cardsOwned->addCard(deck->draw());
                    }

                    cout << players[i].playername << ": ";
                    for (int k = 0; k < 2; k++)
                    {
                        cout << players[i].cardsOwned->cards[k]->type << ", ";
                    }
                    cout << endl;
                }
                cout << endl;

                game->setState(new ReinforcementsState());
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

// Assign reinforcements state
void ReinforcementsState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Assign reinforcements state" << endl;
    for (int i = 0; i < numPlayers; i++)
    {
        reinforcementPhase(players[i]);
    }

    string command;
    while (true)
    {
        cout << "Enter next command: ";
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

void ReinforcementsState::reinforcementPhase(Player &player)
{

    cout << "Reinforcement phase for player: " << player.playername << endl;
    // Reinforcements
    cout << "Player " << player.playername << " number of reinforcements: " << endl;
    int numTerritoriesOwned = player.territoriesOwned.size();
    int numReinforcementsFromTerritories = floor(numTerritoriesOwned / 3);
    cout << "Number of Reinforcements from Territories: " << numReinforcementsFromTerritories << endl;
    // check for continent control here
    int numReinforcementsFromContinents = 0;

    cout << "Number of Reinforcements from Continents: " << numReinforcementsFromContinents << endl;
    int totalReinforcements = numReinforcementsFromTerritories + numReinforcementsFromContinents;
    if (totalReinforcements < 3)
    {
        totalReinforcements = 3;
    }    
    player.reinforcementPool += totalReinforcements;

    cout << "Total Reinforcements for player " << player.playername << ": " << player.reinforcementPool << " armies " << endl;
    cout << endl; 

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

    for (int i = 0; i < numPlayers; i++)
    {
        issueOrdersPhase(players[i]);
    }

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
            game->setState(new ExecuteOrdersState());
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}

void IssueOrdersState::issueOrdersPhase(Player &player)
{
    cout << "Issue orders phase" << endl;

    // for (int i = 0; i < map.GetMap().GetTerritories().size(); i++)
    // {
    //     cout << map.GetMap().GetTerritories()[i]->GetTerritoryName() << " " << map.GetMap().GetTerritories()[i]->GetOwner().playername << endl;
    // }
    // issue orders
    cout << "Issue Order phase for player: " << player.playername << endl;

    player.issueOrder(map, deck, (map.GetMap().GetTerritories().size() / numPlayers));
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

    for (int i = 0; i < numPlayers; i++)
    {
        cout << "Execute Order phase for player: " << players[i].playername << endl;

        executeOrdersPhase(players[i]);
        cout << endl; 
        
        int numTerritoriesOwned = 0;
        for(int j = 0; j < map.GetMap().GetTerritories().size(); j++){
            if(map.GetMap().GetTerritories()[j]->GetOwner().playername == players[i].playername){
                numTerritoriesOwned++;
            }
        }
        // check if player has won
        if (numTerritoriesOwned == map.GetMap().GetTerritories().size())
        {
            cout << "Player " << players[i].playername << " has won the game!" << endl;
            // set the game state to win state
            game->setState(new WinState());
        }
        // Player p = playerQueue.front();
        // playerQueue.pop();
        // playerQueue.push(p);
    }

    for (int i = 0; i < map.GetMap().GetTerritories().size(); i++)
    {
        cout << map.GetMap().GetTerritories()[i]->GetTerritoryName() << " owned by "
             << map.GetMap().GetTerritories()[i]->GetOwner().playername << ": " <<map.GetMap().GetTerritories()[i]->GetArmyQuantity() << " troops" << endl;
    }

    // Checking if any player is eliminated
    for (int i = 0; i < numPlayers; i++)
    {
        int numTerritoriesOwned = 0;
        for(int j = 0; j < map.GetMap().GetTerritories().size(); j++){
            if(map.GetMap().GetTerritories()[j]->GetOwner().playername == players[i].playername){
                numTerritoriesOwned++;
            }
        }
        if (numTerritoriesOwned == 0)
        {
            cout << "Player " << players[i].playername << " has been eliminated from the game!" << endl;
            players.erase(players.begin() + i);
        }
    }

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
void ExecuteOrdersState::executeOrdersPhase(Player &player)
{
    // executes deploy orders
    player.ordersList.executeOrders(map);

    // this one is looping thru maps
    
    cout << "im in the execute orders phase" << endl;
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
