#include <iostream>
#include <string>
#include "Player.cpp"
#include "Player.h"
#include <vector>
using namespace std;

int main() {

//Temporary arbitrary values
vector<string> cards{"Reinforce", "Airlift", "Diplomacy"};
vector<string> terr{"Austria", "France", "Spain", "Germany"};
vector<string> orders{"Bomb", "Blockade"};

vector<string> defend{"Austria", "Germany"};
vector<string> attack{"Italy", "Switzerland"};

//Create player
Player player(cards, terr, orders, defend, attack);


//Display attributes
cout << "Cards: ";
for (int i = 0; i < player.cardsOwned.size(); i++) {
  cout << player.cardsOwned[i] << " ";  
}
cout << endl;

cout << "Territories: ";
for (int i = 0; i < player.territoriesOwned.size(); i++) {
  cout << player.territoriesOwned[i] << " ";  
}
cout << endl;

cout << "Orders: ";
for (int i = 0; i < player.ordersList.size(); i++) {
  cout << player.ordersList[i] << " ";  
}
cout << endl << endl;

//Demonstrate toDefend
vector<string> defending = toDefend(player);
cout << "Player is defending: ";
   for (int i = 0; i < defending.size(); i++) {
        cout << defending[i] << " ";  
    }

//Demonstrate toAttack
vector<string> attacking = toAttack(player);
cout << endl;
cout << "Player is attacking: ";
   for (int i = 0; i < attacking.size(); i++) {
        cout << attacking[i] << " ";  
    }


};