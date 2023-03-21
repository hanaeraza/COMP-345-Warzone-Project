#include <iostream>
#include <string>
#include "Player.h"
#include "Card.h"
#include "Map.h"
#include <vector>
using namespace std;

int main() {

Player player = Player(); 
Player player2 = Player("Player 2");
cout << "player 2's username: " << player2.playername << endl;

// Arbitrary values
Hand cards;
vector<Territory> terr;

vector<string> defend{"Austria", "Germany"};
vector<string> attack{"Italy", "Switzerland"};

// Create a map and get territories
Map map = Map("europe.map");

for (int i = 0; i < map.GetTerritories().size(); i++)
{
  if (i % 2 == 0)
  {
    terr.push_back(map.GetTerritories()[i]);
  }
  
}

// Create hand of 5 cards from deck
Hand* hand = new Hand();
Deck* deck = new Deck();

	for (int i = 0; i < 5; i++) {
		hand->addCard(deck->draw());
	}

// Demonstrate issueOrder
player.issueOrder("Deploy");
player.issueOrder("Negotiate");

player.cardsOwned = hand;
player.territoriesOwned = terr;
player.defenseList = defend;
player.attackList = attack; 


// Print hand of cards
hand->printHand();

// Print territories owned
cout << "Territories: ";
for (int i = 0; i < player.territoriesOwned.size(); i++) {
  cout << player.territoriesOwned[i] << " ";  
}
cout << endl; 

// Print list of orders
cout << "Orders: " << endl;
printOrders(player.ordersList.getOrders());
cout << endl;

//Demonstrate toDefend
vector<string> defending = player.toDefend();
cout << "Player is defending: ";
   for (int i = 0; i < defending.size(); i++) {
        cout << defending[i] << " ";  
    }

//Demonstrate toAttack
vector<string> attacking = player.toAttack();
cout << endl;
cout << "Player is attacking: ";
   for (int i = 0; i < attacking.size(); i++) {
        cout << attacking[i] << " ";  
    }




};