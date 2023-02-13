#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include "Card.h"
using namespace std;


class Player {

    public:
        Hand* cardsOwned; //change string to the cards object later
        vector<string> territoriesOwned; //change string to territories object later
        vector<string> ordersList; //change to orders list object later
        vector<string> defenseList; 
        vector<string> attackList;
        

        Player() {}; //Default constructor
        Player(Hand* cards, vector<string> territories, vector<string> orders, vector<string> defend, vector<string> attack) {
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


/* class Territory {

    public: 
        string name;
        int armies;
        string continent;
        string owner;

        Territory() {}; //Default
        Territory(string n, int a, string c, string o) {
            name = n;
            armies = a;
            continent = c;
            owner = o;
        };
}; */




#endif