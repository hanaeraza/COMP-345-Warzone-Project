#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Player {

    public:
        vector<string> cardsOwned; //change string to the cards object later
        vector<string> territoriesOwned; //change string to territories object later
        vector<string> ordersList; //change to orders list object later
        vector<string> defenseList; 
        vector<string> attackList;

        Player() {}; //Default constructor
        Player(vector<string> cards, vector<string> territories, vector<string> orders, vector<string> defend, vector<string> attack) {
            cardsOwned = cards;
            territoriesOwned = territories;
            ordersList = orders;
            defenseList = defend;
            attackList = attack;
        };

        //Function declarations
        vector<string> toDefend(Player player);
        vector<string> toAttack(Player player);
};





#endif