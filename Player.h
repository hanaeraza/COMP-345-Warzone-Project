#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

// Forward declaration
class Territory;
class Hand;
class OrdersList;


//Player class
class Player {

    public:
        Hand* cardsOwned; 
        vector<Territory> *territoriesOwned; 
        OrdersList *ordersList; 
        vector<string> defenseList; 
        vector<string> attackList;
        

        Player() {}; //Default constructor
        Player(Hand* cards, vector<Territory> *territories, OrdersList *orders, vector<string> defend, vector<string> attack);


        //Function declarations
        static vector<string> toDefend(Player player);
        static vector<string> toAttack(Player player);
        static OrdersList issueOrder();

        // Stream insertion operators
        friend ostream& operator <<(ostream& os, const Player& other);
	    bool operator ==(const Player &other);
};




#endif