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
        Player(string name) {
            playername = name;
            reinforcementPool = 0;
        };
        Player(string name, string strat) {
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
        };
        Player(Hand *cards, vector<Territory> territories, OrdersList orders, vector<string> defend, vector<string> attack, int reinforcements) {
            cardsOwned = cards;
            territoriesOwned = territories;
            ordersList = orders;
            defenseList = defend;
            attackList = attack;
            reinforcementPool = reinforcements;
        };
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
