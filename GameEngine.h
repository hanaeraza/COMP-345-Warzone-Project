#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <iostream>
#include <utility>
#include <unordered_map>
#include "Map.h"
#include "LoggingObserver.h"
#include "CommandProcessor.h"

using namespace std;

class CommandProcessor;
class State;

struct PairHasher {
  size_t operator()(const pair<string, unsigned int>& p) const {
    hash<string> str_hash;
    hash<unsigned int> int_hash;
    return str_hash(p.first) ^ int_hash(p.second);
  }
};

struct MapHasher {
  size_t operator()(const unordered_map<pair<string, unsigned int>, string>& m) const {
    size_t hash_val = 0;
    for (const auto& p : m) {
      hash_val ^= PairHasher()(p.first) ^ hash<string>()(p.second);
    }
    return hash_val;
  }
};

struct TournamentInfo : public Subject, public ILoggable
{
    LogObserver* logger;
    vector<string>* maps;
    vector<string>* players;
    unsigned int* gamesPlayed;
    unsigned int* maxTurns;
    bool* autoResolve;
    vector<double>* autoResolveWeights;

    string* currentMap;
    unsigned int* currentGame;
    bool* playingGame;

    // map, game won, winning player
    unordered_map<pair<string, unsigned int>, string, PairHasher>* winningPlayers;

    string stringToLog() const override;

    friend ostream& operator<<(ostream& os, const TournamentInfo& input);

    TournamentInfo(vector<string> maps, vector<string> players, unsigned int gamesPlayed, unsigned int maxTurns,
                   LogObserver* loggerInput, bool autoResolve = false, vector<double> autoResolveWeights = vector<double>());

    string weightedChoosePlayer();

    void onGameWon(string player = "Draw");
};

class GameEngine : public Subject, public ILoggable
{
public:
    GameEngine();
    GameEngine(const GameEngine& s);
    
    void setState(State *state);
    void update();
    string getCurrentState();

    string stringToLog() const override;

    void setCommandProcessor(CommandProcessor *commandProcessor);
    void setAutoCommandProcessor(string file);
    CommandProcessor getCommandProcessor();
    void setMapLoader(MapLoader *input);
    MapLoader getMapLoader();
    LogObserver* getInnerEngineLogger();

    void generateLogger(string file);

    friend ostream& operator<<(ostream& os, const GameEngine& input);
    
    void mainGameLoop(GameEngine *game);

    void onTournamentStart(TournamentInfo tournamentInfo);

    void onGameWon(string player = "Draw");

    void setTournamentInfo(TournamentInfo* input);
    void setInTournamentMode(bool* input);

    TournamentInfo getTournamentInfo();
    bool isInTournamentMode();

    void setAutoResolve(bool input);
    void setAutoResolveWeights(vector<double> input);

    void setMaxTurns(unsigned int input);
    bool drawCondition();

    void resetTurnCounter();
    void incrementTurnCounter();
    
private:
    State* currentState;
    CommandProcessor* commandProcessor;
    LogObserver* innerEngineLogger;
    MapLoader* mapLoader;
    bool* inTournamentMode;
    TournamentInfo* tournamentInfo;
    bool* autoResolve;
    vector<double>* autoResolveWeights;

    unsigned int* turnCounter;
    unsigned int* maxTurns;
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
    string getName();
    void reinforcementPhase(Player player);

};

class IssueOrdersState : public State
{
public:
    
    void update(GameEngine *game);
    string getName();
    void issueOrdersPhase(Player &player);

};

class ExecuteOrdersState : public State
{
public:
    
    void update(GameEngine *game);
    string getName();
    void executeOrdersPhase(Player &player);

};


class WinState : public State
{
// private:
//     Player winner;
// public:
//     WinState() = default;
//     WinState(Player winner){
//         this->winner = winner;
//     }
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
