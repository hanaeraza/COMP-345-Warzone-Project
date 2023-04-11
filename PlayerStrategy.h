#pragma once
#include "Player.h"
#include <iostream>

using namespace std; 

class MapLoader;
class Territory;

class PlayerStrategy {
    public: 
        virtual void issueOrder(MapLoader currentMap, Deck *deck) = 0; 
        virtual vector<string> toAttack() = 0; 
        virtual vector<string> toDefend() = 0; 
        ~PlayerStrategy() {};
};

//  requires user interactions to make decisions.
class HumanPlayerStrategy : public PlayerStrategy {
  public: 
    void issueOrder(MapLoader currentMap, Deck *deck);
    vector<string> toAttack();
    vector<string> toDefend();
    ~HumanPlayerStrategy() {};

};

// computer player that focuses on attack (deploys or advances armies on its strongest country, 
// then always advances to enemy territories until it cannot do so anymore).
class AggressivePlayerStrategy : public PlayerStrategy {
  public: 
    void issueOrder(MapLoader currentMap, Deck *deck);
    vector<string> toAttack();
    vector<string> toDefend();
    ~AggressivePlayerStrategy() {};

};

// computer player that focuses on protecting its weak countries (deploys or advances armies 
// on its weakest countries, never advances to enemy territories).

class BenevolentPlayerStrategy : public PlayerStrategy {
  public: 
    void issueOrder(MapLoader currentMap, Deck *deck);
    vector<string> toAttack();
    vector<string> toDefend();
    ~BenevolentPlayerStrategy() {};

};


// computer player that never issues any order. If a Neutral player is attacked, it becomes an Aggressive player.
class NeutralPlayerStrategy : public PlayerStrategy {
  public: 
    void issueOrder(MapLoader currentMap, Deck *deck);
    vector<string> toAttack();
    vector<string> toDefend();
    ~NeutralPlayerStrategy() {};

};

// computer player that automatically conquers all territories that are adjacent to its own territories (only once per turn).

class CheaterPlayerStrategy : public PlayerStrategy {
  public: 
    void issueOrder(MapLoader currentMap, Deck *deck);
    vector<string> toAttack();
    vector<string> toDefend();
    ~CheaterPlayerStrategy() {};

};
