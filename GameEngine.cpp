#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <queue>

#include "GameEngine.h"
#include "CommandProcessor.h"
#include "LoggingObserver.h"
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
GameEngine::GameEngine()  : Subject(), currentState(new StartState()) {}

// Function to set next state
void GameEngine::setState(State *state)
{
    currentState = state;
}

void GameEngine::update()
{
    currentState->update(this);
    notify(this);
}

ostream& operator<<(ostream& os, const GameEngine& input){
    os << "Current state: " << input.currentState->getName() << endl;
    return os;
}

string GameEngine::stringToLog() const
{
    stringstream stream;
    string output;
    stream << *this;
    output = stream.str();
    return output;
}

void GameEngine::setCommandProcessor(CommandProcessor *commandProcessor)
{
    this->commandProcessor = commandProcessor;
    commandProcessor->attach(innerEngineLogger);
}

void GameEngine::setAutoCommandProcessor(string file)
{
    commandProcessor = new FileCommandProcessorAdapter(file);
    commandProcessor->attach(innerEngineLogger);
}

CommandProcessor GameEngine::getCommandProcessor()
{
    return *commandProcessor;
}

LogObserver* GameEngine::getInnerEngineLogger(){
    return innerEngineLogger;
}

void GameEngine::setMapLoader(MapLoader *input){
    map = *input;
}
MapLoader GameEngine::getMapLoader(){
    return map;
}

void GameEngine::generateLogger(string file){
    innerEngineLogger = new LogObserver(file);
    attach(innerEngineLogger);
}

string GameEngine::getCurrentState()
{
    return currentState->getName();
}

TournamentInfo::TournamentInfo(vector<string> maps, vector<string> players, unsigned int gamesPlayed, unsigned int maxTurns){
    this->maps = new vector<string>(maps);
    this->players = new vector<string>(players);
    this->gamesPlayed = new unsigned int(gamesPlayed);
    this->maxTurns = new unsigned int(maxTurns);
    this->winningPlayers = new unordered_map<pair<string, unsigned int>, string>();
}

ostream& operator<<(ostream& os, const TournamentInfo& input){
    os << "Tournament Info: " << endl;
    os << "M: " << endl;
    for (int i = 0; i < input.maps->size(); i++){
        os << "\t" << (*(input.maps))[i] << endl;
    }
    os << "P: " << endl;
    for (int i = 0; i < input.players->size(); i++){
        os << "\t" << (*(input.players))[i] << endl;
    }
    os << "G: " << *input.gamesPlayed << endl;
    os << "D: " << *input.maxTurns << endl;

    os << "Results: " << endl;

    os << "\t" << endl;

    for (size_t i = 0; i < *input.gamesPlayed; i++)
    {
        os << "\t" << "Game " << i + 1 << ": " << endl;
    }

    for (size_t i = 0; i < input.maps->size(); i++)
    {
        os << "\t" << "Map " << i + 1 << ": " << endl;
        for (size_t j = 0; j < *input.gamesPlayed; j++)
        {
            os << "\t" << (*(input.winningPlayers))[pair<string, unsigned int>((*(input.maps))[i], j)];
        }
    }

    return os;
}

string TournamentInfo::stringToLog() const
{
    stringstream stream;
    string output;
    stream << *this;
    output = stream.str();
    return output;
}

void TournamentInfo::onGameWon(string player)
{
    (*(winningPlayers))[pair<string, unsigned int>(*currentMap, *currentGame)] = player;
}

void GameEngine::onGameWon(string player)
{
    tournamentInfo->onGameWon(player);
}

//Called when starting a tournament
//Gives Command Processor a list of commands to execute for the tournament
void GameEngine::onTournamentStart(TournamentInfo tournamentInfo)
{
    *inTournamentMode = true;
    this->tournamentInfo = &tournamentInfo;

    for (int i = 0; i < tournamentInfo.maps->size(); i++)
    {
        tournamentInfo.currentMap = &(*(tournamentInfo.maps))[i];

        for (int j = 0; j < *(tournamentInfo.gamesPlayed); j++)
        {
            commandProcessor->clear();
            commandProcessor->saveCommand(Command("loadmap " + (*(tournamentInfo.maps))[i]));
            commandProcessor->saveCommand(Command("validatemap"));
            for (int k = 0; k < min(6, (int)tournamentInfo.players->size()); k++)
            {
                commandProcessor->saveCommand(Command("addplayer " + (*(tournamentInfo.players))[k]));
            }

            tournamentInfo.currentGame = reinterpret_cast<unsigned int*>(&j);

            setState(new StartState());
            update();
        }
    }

    *inTournamentMode = false;
}

void GameEngine::setTournamentInfo(TournamentInfo* input)
{
    tournamentInfo = input;
}

void GameEngine::setInTournamentMode(bool* input)
{
    inTournamentMode = input;
}

TournamentInfo GameEngine::getTournamentInfo()
{
    return *tournamentInfo;
}

bool GameEngine::isInTournamentMode()
{
    return *inTournamentMode;
}

// Start state
void StartState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Start state." << endl;

    string input;
    string command;
    string filename;
    while (game->getCommandProcessor().size() > 0)
    {
        Command nextCommand = game->getCommandProcessor().getCommand();
        nextCommand.attach(game->getInnerEngineLogger());

        command = *(nextCommand.functionName);

        if (nextCommand.parameters->size() > 0)
        {
            filename = (*(nextCommand.parameters))[0];
        }


        if (command.find("tournament") == 0) {
            //takes the substring that's after "tournament"
            std::string argString = command.substr(10);
            std::istringstream iss(argString);

            //initialize variables
            std::vector<std::string> maps;
            std::vector<std::string> players;
            unsigned int gamesPlayed = 0;
            unsigned int maxTurns = 0;

            // Parse the arguments using the input string stream
            std::string arg;
            while (iss >> arg) {
                if (arg == "-M") {
                    // Parse the map files
                    while (iss >> arg && arg[0] != '-') {
                        maps.push_back(arg);
                    }
                } 
                else if (arg == "-P") {
                    // Parse the player strategies
                    while (iss >> arg && arg[0] != '-') {
                    players.push_back(arg);
                    }
                }
                else if (arg == "-G") {
                // Parse the number of games
                iss >> gamesPlayed;
                }
                else if (arg == "-D") {
                // Parse the maximum number of turns
                iss >> maxTurns;
                }
                else {
                std::cout << "Invalid argument: " << arg << std::endl;
                }
            }

            game->setTournamentInfo(new TournamentInfo(maps, players, gamesPlayed, maxTurns));

            game->onTournamentStart(game->getTournamentInfo());
        }

        else if (command == "loadmap" && !filename.empty())
        {
            nextCommand.saveEffect("Loading " + filename + 
            "\nmoving to MapLoadedState.");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();

            try
            {
                MapLoader map = MapLoader(filename);
                game->setMapLoader(&map);
                game->setState(new MapLoadedState());
                return;
            }
            catch (const std::exception& e)
            {
                cout << e.what() << endl;
            }
        }
        else
        {
            nextCommand.saveEffect("Invalid");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();
            cout << "Invalid command" << endl;
        }
    }
    
    while (true)
    {
        cout << "Enter next command: ";
        game->getCommandProcessor().readCommand();

        Command nextCommand = game->getCommandProcessor().getCommand();
        nextCommand.attach(game->getInnerEngineLogger());

        command = *(nextCommand.functionName);

        if (nextCommand.parameters->size() > 0)
        {
            filename = (*(nextCommand.parameters))[0];
        }

        bool valid = game->getCommandProcessor().validate(this);

        if (command.find("tournament") == 0) {
            //takes the substring that's after "tournament"
            std::string argString = command.substr(10);
            std::istringstream iss(argString);

            //initialize variables
            std::vector<std::string> maps;
            std::vector<std::string> players;
            unsigned int gamesPlayed = 0;
            unsigned int maxTurns = 0;

            // Parse the arguments using the input string stream
            std::string arg;
            while (iss >> arg) {
                if (arg == "-M") {
                    // Parse the map files
                    while (iss >> arg && arg[0] != '-') {
                        maps.push_back(arg);
                    }
                } 
                else if (arg == "-P") {
                    // Parse the player strategies
                    while (iss >> arg && arg[0] != '-') {
                    players.push_back(arg);
                    }
                }
                else if (arg == "-G") {
                // Parse the number of games
                iss >> gamesPlayed;
                }
                else if (arg == "-D") {
                // Parse the maximum number of turns
                iss >> maxTurns;
                }
                else {
                std::cout << "Invalid argument: " << arg << std::endl;
                }
            }

            game->setTournamentInfo(new TournamentInfo(maps, players, gamesPlayed, maxTurns));

            game->onTournamentStart(game->getTournamentInfo());
        }
        else if (command == "loadmap" && !filename.empty() && game->getCommandProcessor().validate(this))
        {
            nextCommand.saveEffect("Loading " + filename + 
            "\nmoving to MapLoadedState.");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();

            try
            {
                MapLoader map = MapLoader(filename);
                game->setMapLoader(&map);
                game->setState(new MapLoadedState());
                break;
            }
            catch (const std::exception& e)
            {
                cout << e.what() << endl;
            }
        }
        else
        {
            nextCommand.saveEffect("Invalid");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();
            cout << "Invalid command" << endl;
        }
    }
}

string StartState::getName()
{
    return "start";
}



// Map loaded state
void MapLoadedState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Map loaded state" << endl;

    string input;
    string command;
    string command2;
    while (game->getCommandProcessor().size() > 0)
    {
        cout << "Enter next command: ";

        Command nextCommand = game->getCommandProcessor().getCommand();
        nextCommand.attach(game->getInnerEngineLogger());

        command = *(nextCommand.functionName);

        if (nextCommand.parameters->size() > 0)
        {
            command2 = (*(nextCommand.parameters))[0];
        }

        if (command == "loadmap" && !command2.empty() && game->getCommandProcessor().validate(this))
        {
            nextCommand.saveEffect("Loading " + command2);
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();

            try
            {
                MapLoader map = MapLoader(command2);
                game->setMapLoader(&map);
                game->setState(new MapLoadedState());
                return;
            }
            catch (const std::exception& e)
            {
                cout << e.what() << endl;
            }
        }
        else if (command == "validatemap" && game->getCommandProcessor().validate(this))
        {
            
            bool validated = game->getMapLoader().GetMap().Validate();
            if (validated){
                nextCommand.saveEffect("Map Valid");
                game->getCommandProcessor().saveCommand(nextCommand);
                game->getCommandProcessor().next();
                game->setState(new MapValidatedState());
            }
            else{
                nextCommand.saveEffect("Map Invalid");
                game->getCommandProcessor().saveCommand(nextCommand);
                game->getCommandProcessor().next();
            }
            return;
        }
        
        else
        {
            nextCommand.saveEffect("Invalid");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();
            cout << "Invalid command" << endl;
        }
    }
    while (true)
    {
        cout << "Enter next command: ";
        game->getCommandProcessor().readCommand();

        Command nextCommand = game->getCommandProcessor().getCommand();
        nextCommand.attach(game->getInnerEngineLogger());

        command = *(nextCommand.functionName);

        if (nextCommand.parameters->size() > 0)
        {
            command2 = (*(nextCommand.parameters))[0];
        }

        if (command == "loadmap" && !command2.empty() && game->getCommandProcessor().validate(this))
        {
            nextCommand.saveEffect("Loading " + command2);
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();

            try
            {
                MapLoader map = MapLoader(command2);
                game->setMapLoader(&map);
                game->setState(new MapLoadedState());
                break;
            }
            catch (const std::exception& e)
            {
                cout << e.what() << endl;
            }
        }
        else if (command == "validatemap" && game->getCommandProcessor().validate(this))
        {
            
            bool validated = game->getMapLoader().GetMap().Validate();
            if (validated){
                nextCommand.saveEffect("Map Valid");
                game->getCommandProcessor().saveCommand(nextCommand);
                game->getCommandProcessor().next();
                game->setState(new MapValidatedState());
            }
            else{
                nextCommand.saveEffect("Map Invalid");
                game->getCommandProcessor().saveCommand(nextCommand);
                game->getCommandProcessor().next();
            }
            break;
        }
        
        else
        {
            nextCommand.saveEffect("Invalid");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();
            cout << "Invalid command" << endl;
        }
    }
}

string MapLoadedState::getName()
{
    return "maploaded";
}



// Map validated state
void MapValidatedState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Map validated state" << endl;

    string input;
    string command;
    string parameter;
    while (game->getCommandProcessor().size() > 0)
    {
        Command nextCommand = game->getCommandProcessor().getCommand();
        nextCommand.attach(game->getInnerEngineLogger());

        command = *(nextCommand.functionName);

        if (nextCommand.parameters->size() > 0)
        {
            parameter = (*(nextCommand.parameters))[0];
        }

        if (command == "addplayer" && !parameter.empty() && game->getCommandProcessor().validate(this))
        {
            nextCommand.saveEffect("Adding " + parameter + 
            "\nmoving to PlayersAddedState.");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();

            try
            {
                numPlayers++;
                players.push_back(Player(parameter));
                cout << numPlayers << endl;
                game->setState(new PlayersAddedState());
                return;
            }
            catch (const std::exception& e)
            {
                cout << e.what() << endl;
            }
        }
        else
        {
            nextCommand.saveEffect("Invalid");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();
            cout << "Invalid command" << endl;
        }
    }
    
    while (true)
    {
        game->getCommandProcessor().readCommand();

        Command nextCommand = game->getCommandProcessor().getCommand();
        nextCommand.attach(game->getInnerEngineLogger());

        command = *(nextCommand.functionName);

        if (nextCommand.parameters->size() > 0)
        {
            parameter = (*(nextCommand.parameters))[0];
        }

        if (command == "addplayer" && !parameter.empty() && game->getCommandProcessor().validate(this))
        {
            nextCommand.saveEffect("Adding " + parameter + 
            "\nmoving to PlayersAddedState.");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();

            try
            {
                numPlayers++;
                players.push_back(Player(parameter));
                cout << numPlayers << endl;
                game->setState(new PlayersAddedState());
                break;
            }
            catch (const std::exception& e)
            {
                cout << e.what() << endl;
            }
        }
        else
        {
            nextCommand.saveEffect("Invalid");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();
            cout << "Invalid command" << endl;
        }
    }
}

string MapValidatedState::getName()
{
    return "mapvalidated";
}



// Players added state
void PlayersAddedState::update(GameEngine *game)
{
    cout << "-----------------------------------" << endl;
    cout << "Players Added state" << endl;

    string input;
    string command;
    string parameter;
    while (game->getCommandProcessor().size() > 0)
    {
        Command nextCommand = game->getCommandProcessor().getCommand();
        nextCommand.attach(game->getInnerEngineLogger());

        command = *(nextCommand.functionName);

        if (nextCommand.parameters->size() > 0)
        {
            parameter = (*(nextCommand.parameters))[0];
        }

        if (command == "addplayer" && !parameter.empty() && game->getCommandProcessor().validate(this))
        {
            nextCommand.saveEffect("Adding " + parameter + 
            "\nmoving to PlayersAddedState.");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();

            try
            {
                numPlayers++;
                players.push_back(Player(parameter));
                cout << numPlayers << endl;
                game->setState(new PlayersAddedState());
                return;
            }
            catch (const std::exception& e)
            {
                cout << e.what() << endl;
            }
        }
        else if (command == "gamestart" && parameter.empty() && game->getCommandProcessor().validate(this))
        {
            if (numPlayers > 6 || numPlayers < 2)
            {
                nextCommand.saveEffect("You need between 2 and 6 players to start!");
                game->getCommandProcessor().saveCommand(nextCommand);
                game->getCommandProcessor().next();
            }
            else
            {
                nextCommand.saveEffect("Starting Game");
                game->getCommandProcessor().saveCommand(nextCommand);
                game->getCommandProcessor().next();
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

                for (int i = 0; i < numPlayers; i++)
                {
                    playerQueue.push(players[i]);
                }

                game->setState(new ReinforcementsState());
                break;
            }
        }
        
        else
        {
            nextCommand.saveEffect("Invalid");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();
            cout << "Invalid command" << endl;
        }
    }
    
    while (true)
    {
        game->getCommandProcessor().readCommand();

        Command nextCommand = game->getCommandProcessor().getCommand();
        nextCommand.attach(game->getInnerEngineLogger());

        command = *(nextCommand.functionName);

        if (nextCommand.parameters->size() > 0)
        {
            parameter = (*(nextCommand.parameters))[0];
        }

        if (command == "addplayer" && !parameter.empty() && game->getCommandProcessor().validate(this))
        {
            nextCommand.saveEffect("Adding " + parameter + 
            "\nmoving to PlayersAddedState.");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();

            try
            {
                numPlayers++;
                players.push_back(Player(parameter));
                cout << numPlayers << endl;
                game->setState(new PlayersAddedState());
                break;
            }
            catch (const std::exception& e)
            {
                cout << e.what() << endl;
            }
        }
        else if (command == "gamestart" && parameter.empty() && game->getCommandProcessor().validate(this))
        {
            if (numPlayers > 6 || numPlayers < 2)
            {
                nextCommand.saveEffect("You need between 2 and 6 players to start!");
                game->getCommandProcessor().saveCommand(nextCommand);
                game->getCommandProcessor().next();
            }
            else
            {
                nextCommand.saveEffect("Starting Game");
                game->getCommandProcessor().saveCommand(nextCommand);
                game->getCommandProcessor().next();
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

                for (int i = 0; i < numPlayers; i++)
                {
                    playerQueue.push(players[i]);
                }

                game->setState(new ReinforcementsState());
                break;
            }
        }
        
        else
        {
            nextCommand.saveEffect("Invalid");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();
            cout << "Invalid command" << endl;
        }
    }
}

string PlayersAddedState::getName()
{
    return "playersadded";
}

// void GameEngine::mainGameLoop(GameEngine *game)
// {
//     while (true)
//     {
//         cout << "-----------------------------------" << endl;
//         cout << "Main game loop" << endl;
//         cout << "Current player: " << playerQueue.front().playername << endl;
//         game->setState(new ReinforcementsState());
//         cout << "Reinforcements: " << playerQueue.front().reinforcementPool << endl;
//         game->setState(new IssueOrdersState());

//         game->setState(new ExecuteOrdersState());

//         Player p = playerQueue.front();
//         playerQueue.pop();
//         playerQueue.push(p);
//     }
// }


// Assign reinforcements state
void ReinforcementsState::update(GameEngine *game)
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

            game->setState(new IssueOrdersState());
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
    for (int i = 0; i < playerQueue.size(); i++)
    {
        cout << "Reinforcement phase for player: " << playerQueue.front().playername << endl;
        // Reinforcements
        cout << "Player " << playerQueue.front().playername << " number of reinforcements: " << endl;
        int numTerritoriesOwned = playerQueue.front().territoriesOwned.size();
        int numReinforcementsFromTerritories = floor(numTerritoriesOwned / 3);
        cout << "Number of Reinforcements from Territories: " << numReinforcementsFromTerritories << endl;
        // check for continent control here
        int numReinforcementsFromContinents = 0;
        // vector<string> continentsOwned = map.GetMap().GetContinentsOwnedBy(playerQueue.front());
        // if(continentsOwned.size() != 0){
        //     for (int i = 0; i < continentsOwned.size(); i++)
        //     {
        //         numReinforcementsFromContinents += map.GetMap().GetContinentBonus(continentsOwned[i]);
        //     }
        // }
        // else{
        //     cout << "No continents owned" << endl;
        //     numReinforcementsFromContinents = 0;
        // }

        cout << "Number of Reinforcements from Continents: " << numReinforcementsFromContinents << endl;
        int totalReinforcements = numReinforcementsFromTerritories + numReinforcementsFromContinents;
        if (totalReinforcements < 3)
        {
            totalReinforcements = 3;
        }
        cout << "Total Reinforcements for player " << playerQueue.front().playername << ": " << totalReinforcements << " armies " << endl;
        cout << playerQueue.front().reinforcementPool << endl;
        playerQueue.front().reinforcementPool += totalReinforcements;
        cout << playerQueue.front().reinforcementPool << endl;
        // switch to next player
        Player p = playerQueue.front();
        playerQueue.pop();
        playerQueue.push(p);
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
            game->setState(new ExecuteOrdersState());
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
    cout << "Issue orders phase" << endl;
    for (int i = 0; i < playerQueue.size(); i++)
    {
        // issue orders
        cout << "Issue Order phase for player: " << playerQueue.front().playername << endl;
        playerQueue.front().issueOrder(map, deck);
        // swictch player
        Player p = playerQueue.front();
        playerQueue.pop();
        playerQueue.push(p);
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

    for (int i = 0; i < playerQueue.size(); i++)
    {
        cout << "Execute Order phase for player: " << playerQueue.front().playername << endl;

        executeOrdersPhase(playerQueue.front());
        
        // check if player has won
        if (playerQueue.front().territoriesOwned.size() == map.GetMap().GetTerritories().size())
        {
            cout << "Player " << playerQueue.front().playername << " has won the game!" << endl;
            // set the game state to win state

            Player p = playerQueue.front();

            game->onGameWon(p.playername);

            if (game->isInTournamentMode())
            {
                return;
            }
            else
                game->setState(new WinState());
        }
        Player p = playerQueue.front();
        playerQueue.pop();
        playerQueue.push(p);
    }
    //Checking if any player is eliminated
    for(int i = 0; i < playerQueue.size(); i++){
        if(playerQueue.front().territoriesOwned.size() == 0){
            cout << "Player " << playerQueue.front().playername << " has been eliminated from the game!" << endl;
            playerQueue.pop();
        }
        else{
            Player p = playerQueue.front();
            playerQueue.pop();
            playerQueue.push(p);
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
void ExecuteOrdersState::executeOrdersPhase(Player player)
{
    // so use the player's order list to execute the orders.
    // use a for loop to go through the list and execute each order
    // add an if statement for each type of order
    // for each order, call the validate method
    // if the order is valid, call the execute method
    // make sue deploy orders are executed first
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

    string input;
    string command;
    string parameter;
    while (game->getCommandProcessor().size() > 0)
    {
        Command nextCommand = game->getCommandProcessor().getCommand();
        nextCommand.attach(game->getInnerEngineLogger());

        command = *(nextCommand.functionName);

        if (nextCommand.parameters->size() > 0)
        {
            parameter = (*(nextCommand.parameters))[0];
        }

        if (command == "replay" && game->getCommandProcessor().validate(this))
        {
            nextCommand.saveEffect("Replaying\nmoving to StartState.");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();

            try
            {
                game->setState(new StartState());
                return;
            }
            catch (const std::exception& e)
            {
                cout << e.what() << endl;
            }
        }
        else if (command == "quit" && game->getCommandProcessor().validate(this))
        {
            nextCommand.saveEffect("Quitting\nmoving to EndState.");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();

            try
            {
                game->setState(new EndState());
                return;
            }
            catch (const std::exception& e)
            {
                cout << e.what() << endl;
            }
        }
        
        else
        {
            nextCommand.saveEffect("Invalid");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();
            cout << "Invalid command" << endl;
        }
    }
    
    while (true)
    {
        game->getCommandProcessor().readCommand();

        Command nextCommand = game->getCommandProcessor().getCommand();
        nextCommand.attach(game->getInnerEngineLogger());

        command = *(nextCommand.functionName);

        if (nextCommand.parameters->size() > 0)
        {
            parameter = (*(nextCommand.parameters))[0];
        }

        if (command == "replay" && game->getCommandProcessor().validate(this))
        {
            nextCommand.saveEffect("Replaying\nmoving to StartState.");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();

            try
            {
                game->setState(new StartState());
                break;
            }
            catch (const std::exception& e)
            {
                cout << e.what() << endl;
            }
        }
        else if (command == "quit" && game->getCommandProcessor().validate(this))
        {
            nextCommand.saveEffect("Quitting\nmoving to EndState.");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();

            try
            {
                game->setState(new EndState());
                break;
            }
            catch (const std::exception& e)
            {
                cout << e.what() << endl;
            }
        }
        else
        {
            nextCommand.saveEffect("Invalid");
            game->getCommandProcessor().saveCommand(nextCommand);
            game->getCommandProcessor().next();
            cout << "Invalid command" << endl;
        }
    }
}

string WinState::getName()
{
    return "win";
}

// End state
void EndState::update(GameEngine *game)
{
    // end
}

string EndState::getName()
{
    return "exit program";
}

/* void GameEngine::mainGameLoop(){
    reinforcementPhase();
} */
