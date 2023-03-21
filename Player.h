#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "Orders.h"
#include "Card.h"
#include "Map.h"

using namespace std;

// Forward declaration
class Territory;
class MapLoader;
//Player class
class Player { 

    public:
        string playername;
        Hand *cardsOwned; 
        vector<Territory> territoriesOwned; 
        OrdersList ordersList; 
        vector<string> defenseList; 
        vector<string> attackList;
        int reinforcementPool; 
        

        Player() {}; //Default constructor
        Player(string name) {
            playername = name;
        };
        Player(Hand *cards, vector<Territory> territories, OrdersList orders, vector<string> defend, vector<string> attack, int reinforcements) {
            cardsOwned = cards;
            territoriesOwned = territories;
            ordersList = orders;
            defenseList = defend;
            attackList = attack;
            reinforcementPool = reinforcements;
        };


        //Function declarations (make non static)
        vector<string> toDefend();
        vector<string> toAttack();
        void issueOrder(MapLoader currentMap);

        // Stream insertion operators
        friend ostream& operator <<(ostream& os, const Player& other);
	    bool operator ==(const Player &other);
};




#endif
