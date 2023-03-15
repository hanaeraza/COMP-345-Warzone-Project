#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
// #include "Map.cpp"
#include "Card.cpp"
//#include "Map.cpp"
using namespace std;

class Territory;

//Player class
class Player {

    public:
        Hand* cardsOwned; //change string to the cards object later
        vector<Territory> territoriesOwned; //change string to territories object later
        OrdersList ordersList; //change to orders list object later
        vector<string> defenseList; 
        vector<string> attackList;
        

        Player() {}; //Default constructor
        Player(Hand* cards, vector<Territory> territories, OrdersList orders, vector<string> defend, vector<string> attack) {
            cardsOwned = cards;
            territoriesOwned = territories;
            ordersList = orders;
            defenseList = defend;
            attackList = attack;
        };


        static OrdersList issueOrder();

        //Function declarations
        static vector<string> toDefend(Player player);
        static vector<string> toAttack(Player player);

        // friend ostream& operator <<(ostream& os, const Player& other);
        friend ostream& operator<<(ostream& os, const Player& other) {
            return os;
        }
	    bool operator ==(const Player &other);
};




#endif