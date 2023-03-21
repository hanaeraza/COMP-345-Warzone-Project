#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "Card.h"
#include "Orders.h"
#include "Map.h"
using namespace std;

// Forward declaration
class Territory;

//Player class
class Player { 

    public:
        string playername;
        Hand* cardsOwned = new Hand(); 
        vector<Territory> territoriesOwned; 
        OrdersList ordersList; 
        vector<string> defenseList; 
        vector<string> attackList;
        int reinforcementPool; 
        

        Player() {}; //Default constructor
        Player(string name) {
            playername = name;
        };
        Player(Hand* cards, vector<Territory> territories, OrdersList orders, vector<string> defend, vector<string> attack, int reinforcements) {
            cardsOwned = cards;
            territoriesOwned = territories;
            ordersList = orders;
            defenseList = defend;
            attackList = attack;
            reinforcementPool = reinforcements;
        };


        //Function declarations 
        vector<string> toDefend();
        vector<string> toAttack();
        void issueOrder(string order);

        // Stream insertion operators
        friend ostream& operator <<(ostream& os, const Player& other);
	    bool operator ==(const Player &other);
};




#endif