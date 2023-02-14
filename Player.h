#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "Card.cpp"
//#include "Map.cpp"
using namespace std;

//Player class
class Player {

    public:
        Hand* cardsOwned; //change string to the cards object later
        vector<string> territoriesOwned; //change string to territories object later
        OrdersList ordersList; //change to orders list object later
        vector<string> defenseList; 
        vector<string> attackList;
        

        Player() {}; //Default constructor
        Player(Hand* cards, vector<string> territories, OrdersList orders, vector<string> defend, vector<string> attack) {
            cardsOwned = cards;
            territoriesOwned = territories;
            ordersList = orders;
            defenseList = defend;
            attackList = attack;
        };

        //Function declarations
        vector<string> toDefend(Player player);
        vector<string> toAttack(Player player);

        friend ostream& operator <<(ostream& os, const Player& other);
	    bool operator ==(const Player &other);
};




#endif