#ifndef PLAYER_C
#define PLAYER_C
#include <iostream>
#include <string>
#include "Player.h"
#include <vector>
using namespace std;



 vector<string> Player::toDefend() {

    return this->defenseList;
} 


 vector<string> Player::toAttack() {

    return this->attackList;
} 


// Create an order object and add it to the player's list of orders
void Player::issueOrder(string order) {
    newOrder orderCreate;

    // Arbitrary order
    ordersList.addOrder(orderCreate.createOrder(order));

}

// Stream operators
ostream& operator<<(ostream& os, const Player& other) {
    return os;
}

bool Player::operator==(const Player& other) {
    return true;
}

#endif