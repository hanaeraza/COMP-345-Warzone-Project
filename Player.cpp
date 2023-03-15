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
    orders.addOrder(orderCreate.createOrder("Deploy"));

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