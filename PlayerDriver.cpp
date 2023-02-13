#include <iostream>
#include <string>
#include "Player.cpp"
#include "Player.h"
#include "Card.h"
#include "Card.cpp"
#include <vector>
using namespace std;

int main() {

//Temporary arbitrary values
Hand cards;
vector<string> terr{"France", "Spain", "Austria"};

/* Territory austria{"Austria", 2, "Europe", "Player1"};
Territory france{"France", 6, "Europe", "Player1"};
Territory spain{"Spain", 5, "Europe", "Player1"};
//{"Austria", "France", "Spain", "Germany"};

terr.push_back(austria);
terr.push_back(france);
terr.push_back(spain); */




vector<string> orders{"Bomb", "Blockade"};

vector<string> defend{"Austria", "Germany"};
vector<string> attack{"Italy", "Switzerland"};

// Create hand of 5 cards from deck
Hand* hand = new Hand();
Deck* deck = new Deck();

	for (int i = 0; i < 5; i++) {
		hand->addCard(deck->draw());
	}




//Create player
Player player(hand, terr, orders, defend, attack);

	
//Display attributes
/* cout << "Cards: ";
for (int i = 0; i < player.cardsOwned.size(); i++) {
  cout << player.cardsOwned[i]->type << " ";  
} */
hand->printHand();
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