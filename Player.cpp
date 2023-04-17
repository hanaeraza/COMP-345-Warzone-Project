#ifndef PLAYER_C
#define PLAYER_C
#include <iostream>
#include <string>
#include "Player.h"

#include <vector>
using namespace std;

class MapLoader;
class Territory;

vector<string> Player::toDefend()
{
    return this->strategy->toDefend(this);
}

vector<string> Player::toAttack()
{
     return this->strategy->toAttack(this);
}

// Create an order object and add it to the player's list of orders
void Player::issueOrder(MapLoader currentMap, Deck *deck, int numTerritoriesPerPlayer)
{
    strategy->issueOrder(this,currentMap, deck, numTerritoriesPerPlayer);
}

// Stream operators
ostream &operator<<(ostream &os, const Player &other)
{
    return os;
}

bool Player::operator==(const Player &other)
{
    return playername == other.playername;
}

#endif