#ifndef PLAYER_C
#define PLAYER_C
#include <iostream>
#include <string>
#include "Player.h"

#include <vector>
using namespace std;

class MapLoader;
class Territory;

 vector<string> Player::toDefend() {

    return this->defenseList;
} 


 vector<string> Player::toAttack() {

    return this->attackList;
} 


// Create an order object and add it to the player's list of orders
void Player::issueOrder(MapLoader currentMap) {
    
    OrdersList orders;

    

    vector<int> territoriesOwnedReinforcements;
    cout << "Territories owned: \n";
    for(int i=0; i<this->territoriesOwned.size(); i++){
        
        cout << this->territoriesOwned.at(i).GetTerritoryName() << "\n";
    }
    cout << "Choose a territory to defend:" << "\n";
    while(true){
        string territoryToDefend;
        cin >> territoryToDefend;
        for(int i=0; i<this->territoriesOwned.size(); i++){
            if(territoryToDefend == this->territoriesOwned.at(i).GetTerritoryName()){
                this->defenseList.push_back(territoryToDefend);
                cout << "How many armies would you like to deploy in " + territoriesOwned.at(i).GetTerritoryName() << "\n";
                int numTroopsToDeploy;
                cin >> numTroopsToDeploy;
                territoriesOwnedReinforcements.push_back(numTroopsToDeploy);
                break;
            }
        }
        cout << "Choose another territory to defend:" << "\n";
    }
    cout << "Choose a territory to attack:" << "\n";
    while(true){
        for(int i=0; i<this->territoriesOwned.size(); i++){
            //print connections of each territory
            cout << this->territoriesOwned.at(i).GetTerritoryName() << "Connected to: \n";
            vector<Territory> territoriesConnected = currentMap.GetMap().GetConnections(this->territoriesOwned.at(i));
            for(int j=0; j<territoriesConnected.size(); j++){
                cout << "\t" << territoriesConnected.at(j).GetTerritoryName() << "\n";
            }
            //cout << this->territoriesOwned->at(i).getConnections() << "\n";
        }
        string territoryToAttack;
        cin >> territoryToAttack;
        //verify that territoryToAttack is adjacent to owned territory
        //if it is, add to attackList 
        //if not, ask for another territory
        //repeat until player is satisfied
        attackList.push_back(territoryToAttack);
                
        cout << "Choose another territory to attack:" << "\n";
    }
    /*The player issues deploy orders on its own territories that are in the list returned by toDefend(). As long
as the player has armies still to deploy (see startup phase and reinforcement phase), it will issue a deploy
order and no other order. Once it has deployed all its available armies, it can proceed with other kinds of
orders. */
    //not sure if true
    for(int i=0; i<this->defenseList.size(); i++){
      //  orders.addOrder(Deploy(this,this.defenseList.at(i), territoriesOwnedReinforcements.at(i)));
    }
    /*The player issues advance orders to either (1) move armies from one of its own territory to the other in
order to defend them (using toDefend() to make the decision), and/or (2) move armies from one of its
territories to a neighboring enemy territory to attack them (using toAttack() to make the decision). */
    
    //Attacking
    for(int i=0; i<this->attackList.size(); i++){
      // orders.addOrder(orderCreate.createOrder(Advance(this,this.defenseList.at(i), this.defenseList.at(i), 1))); 
    }
    //de
    /*The player uses one of the cards in their hand to issue an order that corresponds to the card in question. */
    //add choose option

    cout << "Choose a card to play:" << "\n";
    int numberOfCards = sizeof(this->cardsOwned->cards) / sizeof(*(this->cardsOwned->cards));

    // Card ** cards = this->cardsOwned->cards;

    // for(int i=0; i < numberOfCards; i++){ // 
    //    if(this->cardsOwned->cards[1][i].getType() == "Bomb"){
    //          orders.addOrder(orderCreate.createOrder("Bomb"));
    //      }
    //      else if(this->cardsOwned->cards[1][i].getType() == "Blockade"){
    //          orders.addOrder(orderCreate.createOrder("Blockade"));
    //      }
    //      else if(this->cardsOwned->cards[1][i].getType() == "Airlift"){
    //          orders.addOrder(orderCreate.createOrder("Airlift"));
    //      }
    //     else if(this->cardsOwned->cards[1][i].getType() == "Diplomacy"){
    //          orders.addOrder(orderCreate.createOrder("Diplomacy"));
    //      } 
    // }
    
}

// Stream operators
ostream& operator<<(ostream& os, const Player& other) {
    return os;
}

bool Player::operator==(const Player& other) {
    return true;
}

#endif
