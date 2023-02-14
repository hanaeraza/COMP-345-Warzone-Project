#ifndef PLAYER_C
#define PLAYER_C
#include <iostream>
#include <string>
#include "Player.h"
#include <vector>
using namespace std;


 vector<string> toDefend(Player player) {

    return player.defenseList;
} 


 vector<string> toAttack(Player player) {

    return player.attackList;
} 


// Create an order object and add it to the player's list of orders
OrdersList issueOrder() {
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