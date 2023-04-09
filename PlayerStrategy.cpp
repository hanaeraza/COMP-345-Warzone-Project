#pragma once
#include "Player.h"
#include <iostream>

using namespace std; 

class MapLoader;
class Territory;

class PlayerStrategy {
    public: 
        Player* p;
        virtual void issueOrder(MapLoader currentMap, Deck *deck) = 0; 
        virtual void toAttack() = 0; 
        virtual void toDefend() = 0; 
};

//  requires user interactions to make decisions.
class HumanPlayerStrategy : public PlayerStrategy {
    void issueOrder(MapLoader currentMap, Deck *deck) override {
       
        //copy of existing issueOrder
    }

    void toAttack() override {

    }

    void toDefend() override {

    }

};

// computer player that focuses on attack (deploys or advances armies on its strongest country, 
// then always advances to enemy territories until it cannot do so anymore).
class AggressivePlayerStrategy : public PlayerStrategy {
    void issueOrder(MapLoader currentMap, Deck *deck) override {

        // find strongest country, then deploy all armies to it. then advance to enemy territories until run out of armies
    }

    void toAttack() override {

    }

    void toDefend() override {

    }

};

// computer player that focuses on protecting its weak countries (deploys or advances armies 
// on its weakest countries, never advances to enemy territories).
class BenevolentPlayerStrategy : public PlayerStrategy {
    void issueOrder(MapLoader currentMap, Deck *deck) override {

        // find 3 weakest countries, distribute armies equally to 3 weakest countries
        // alternatively, just find the weakest country and deploy all armies to it (easier)

    }

    void toAttack() override {

    }

    void toDefend() override {

    }

};


// computer player that never issues any order. If a Neutral player is attacked, it becomes an Aggressive player.
class NeutralPlayerStrategy : public PlayerStrategy {
    void issueOrder(MapLoader currentMap, Deck *deck) override {

        // check if any of its territories are attacked. if so, become an aggressive player. 
    }

    void toAttack() override {

    }

    void toDefend() override {

    }

};

// computer player that automatically conquers all territories that are adjacent to its own territories (only once per turn).
class CheaterPlayerStrategy : public PlayerStrategy {
    void issueOrder(MapLoader currentMap, Deck *deck) override {

        // automatically conquer all territories adjacent to its own territories
    }

    void toAttack() override {

    }

    void toDefend() override {

    }

};
