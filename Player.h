#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "Orders.h"
#include "Card.h"
#include "Map.h"
#include "PlayerStrategy.h"

using namespace std;

// Forward declaration
class Territory;
class MapLoader;

//Player class
class Player { 
private:
    vector<string> splitStringByCharacter(const string& input, char delimiter) {
        std::vector<std::string> output;
        size_t startIndex = 0;
        size_t endIndex = input.find(delimiter);

        while (endIndex != string::npos) {
            output.push_back(input.substr(startIndex, endIndex - startIndex));
            startIndex = endIndex + 1;
            endIndex = input.find(delimiter, startIndex);
        }
        
        output.push_back(input.substr(startIndex));
        return output;
    }
    void initPlayer(string name, string strat){
        playername = name;
        reinforcementPool = 0;
        if (strat == "human") {
            strategy = new HumanPlayerStrategy(); 
        }
        else if (strat == "aggressive") {
            strategy = new AggressivePlayerStrategy(); 
        }
        else if (strat == "benevolent") {
            strategy = new BenevolentPlayerStrategy(); 
        }
        else if (strat == "neutral") {
            strategy = new NeutralPlayerStrategy(); 
        }
        else if (strat == "cheater") {
            strategy = new CheaterPlayerStrategy(); 
        }
    }

public:
    PlayerStrategy * strategy; 
    string playername;
    Hand *cardsOwned = new Hand(); 
    vector<Territory> territoriesOwned; 
    OrdersList ordersList; 
    vector<string> defenseList; 
    vector<string> attackList;
    int reinforcementPool; 
    

    Player() : reinforcementPool(0) {}; //Default constructor
    Player(string input) {
        vector<string> splitString = splitStringByCharacter(input, '|');

        if (splitString.size() > 1)
            initPlayer(splitString[0], splitString[1]);
        else
            initPlayer(splitString[0], "human");
    };
    Player(string name, string strat) {
        initPlayer(name, strat);
    };
    Player(Hand *cards, vector<Territory> territories, OrdersList orders, vector<string> defend, vector<string> attack, int reinforcements) {
        cardsOwned = cards;
        territoriesOwned = territories;
        ordersList = orders;
        defenseList = defend;
        attackList = attack;
        reinforcementPool = reinforcements;
    };
    Player(const Player& other) {
        if (other.strategy != nullptr) {
            if (dynamic_cast<HumanPlayerStrategy*>(other.strategy) != nullptr) {
                strategy = new HumanPlayerStrategy();
            }
            else if (dynamic_cast<AggressivePlayerStrategy*>(other.strategy) != nullptr) {
                strategy = new AggressivePlayerStrategy();
            }
            else if (dynamic_cast<BenevolentPlayerStrategy*>(other.strategy) != nullptr) {
                strategy = new BenevolentPlayerStrategy();
            }
            else if (dynamic_cast<NeutralPlayerStrategy*>(other.strategy) != nullptr) {
                strategy = new NeutralPlayerStrategy();
            }
            else if (dynamic_cast<CheaterPlayerStrategy*>(other.strategy) != nullptr) {
                strategy = new CheaterPlayerStrategy();
            }
        }
        else {
            strategy = nullptr;
        }

        playername = other.playername;
        cardsOwned = other.cardsOwned;
        territoriesOwned = other.territoriesOwned;
        ordersList = other.ordersList;
        defenseList = other.defenseList;
        attackList = other.attackList;
        reinforcementPool = other.reinforcementPool;
    }; //Copy constructor
    ~Player() {}; //Destructor

    //Function declarations (make non static)
    vector<string> toDefend();
    vector<string> toAttack();
    void issueOrder(MapLoader currentMap, Deck *deck);

    // Stream insertion operators
    friend ostream& operator <<(ostream& os, const Player& other);
    bool operator ==(const Player &other);
};




#endif
