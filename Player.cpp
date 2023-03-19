#ifndef PLAYER_C
#define PLAYER_C
#include <iostream>
#include <string>
#include "Player.h"
#include "Card.h"
#include "Orders.h"
#include "Map.h"

#include <vector>
using namespace std;

Player::Player(Hand* cards, vector<Territory> *territories, OrdersList *orders, vector<string> defend, vector<string> attack, int reinforcments){
    Player::cardsOwned = cards;
    Player::territoriesOwned = territories;
    Player::ordersList = orders;
    Player::defenseList = defend;
    Player::attackList = attack;
    Player::reinforcmentPool = reinforcments;
}
 vector<string> Player::toDefend(Player player) {

    return player.defenseList;
} 


 vector<string> Player::toAttack(Player player) {

    return player.attackList;
} 


// Create an order object and add it to the player's list of orders
OrdersList Player::issueOrder() {
    newOrder orderCreate;
    OrdersList orders;

    // Arbitrary order
    //orders.addOrder(orderCreate.createOrder("Deploy"));
    for(int i=0; i<this->territoriesOwned->size(); i++){
        cout << this->territoriesOwned->at(i).GetTerritoryName() << "\n";
    }
    cout << "Choose a territory to defend:" << "\n";
    while(true){
        string territoryToDefend;
        cin >> territoryToDefend;
        for(int i=0; i<this->territoriesOwned->size(); i++){
            if(territoryToDefend == this->territoriesOwned->at(i).GetTerritoryName()){
                this->defenseList.push_back(territoryToDefend);
                break;
            }
        }
        cout << "Choose another territory to defend:" << "\n";
    }
    cout << "Choose a territory to attack:" << "\n";
    while(true){
        for(int i=0; i<this->territoriesOwned->size(); i++){
            //print connections of each territory
            getConnections(this->territoriesOwned->at(i));
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
        for(int j=0; j<this->territoriesOwned->size(); j++){
            if(this->defenseList.at(i) == this->territoriesOwned->at(j).GetTerritoryName()){
                orders.addOrder(orderCreate.createOrder("Deploy", this->territoriesOwned->at(j).GetTerritoryName(), this->territoriesOwned->at(j).getArmies()));
            }
        }
    }
    /*The player issues advance orders to either (1) move armies from one of its own territory to the other in
order to defend them (using toDefend() to make the decision), and/or (2) move armies from one of its
territories to a neighboring enemy territory to attack them (using toAttack() to make the decision). */
    //not sure if true
    for(int i=0; i<this->defenseList.size(); i++){
        for(int j=0; j<this->territoriesOwned->size(); j++){
            if(this->defenseList.at(i) == this->territoriesOwned->at(j).GetTerritoryName()){
                orders.addOrder(orderCreate.createOrder("Advance", this->territoriesOwned->at(j).GetTerritoryName(), this->territoriesOwned->at(j).getArmies()));
            }
        }
    }
    /*The player uses one of the cards in their hand to issue an order that corresponds to the card in question. */
    //add choose option
    for(int i=0; i<this->cardsOwned->cards.size(); i++){
        if(this->cardsOwned->cards.at(i).getType() == "Bomb"){
            orders.addOrder(orderCreate.createOrder("Bomb"));
        }
        else if(this->cardsOwned->cards.at(i).getType() == "Blockade"){
            orders.addOrder(orderCreate.createOrder("Blockade"));
        }
        else if(this->cardsOwned->cards.at(i).getType() == "Airlift"){
            orders.addOrder(orderCreate.createOrder("Airlift"));
        }
        else if(this->cardsOwned->cards.at(i).getType() == "Diplomacy"){
            orders.addOrder(orderCreate.createOrder("Diplomacy"));
        }
    }
    return orders;
}

// Stream operators
ostream& operator<<(ostream& os, const Player& other) {
    return os;
}

bool Player::operator==(const Player& other) {
    return true;
}

#endif
