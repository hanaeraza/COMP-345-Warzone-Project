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
    int numTroopsRemaining = this->reinforcementPool;
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
                if(numTroopsToDeploy>numTroopsRemaining){
                    cout << "You do not have enough troops to deploy that many. Please try again." << "\n";
                    continue;
                }
                else if(numTroopsToDeploy<1){
                    cout << "You must deploy at least 1 troop. Please try again." << "\n";
                    continue;
                }
                numTroopsRemaining = numTroopsRemaining - numTroopsToDeploy;
                territoriesOwnedReinforcements.push_back(numTroopsToDeploy);
                break;
            }
        }
        if(this->reinforcementPool == 0){
            cout << "You have deployed all your troops." << "\n";
            break;
        }
        else{
            cout << "Choose another territory to defend:" << "\n";
        }
       
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
        for(int i=0;i<this->territoriesOwned.size();i++){
            vector<Territory> territoriesConnected = currentMap.GetMap().GetConnections(this->territoriesOwned.at(i));
            for(int j=0; j<territoriesConnected.size(); j++){
                if(territoryToAttack == territoriesConnected.at(j).GetTerritoryName()){
                    this->attackList.push_back(territoryToAttack);
                    break;
                }
            }
        }
        
        cout << "Choose another territory to attack:" << "\n";
    }
    //Deploying
    for(int i=0; i<this->defenseList.size(); i++){
        //orders.addOrder(new Deploy(this->defenseList.at(i),this, territoriesOwnedReinforcements.at(i)));
    }

    
    //Attacking
    for(int i=0; i<this->attackList.size(); i++){
       //orders.addOrder(new Advance(this.defenseList.at(i), this.defenseList.at(i),this, 1)); 
    }
    
    /*The player uses one of the cards in their hand to issue an order that corresponds to the card in question. */
    //add choose option

    cout << "Choose a card to play:" << "\n";
    int numberOfCards = sizeof(this->cardsOwned->cards) / sizeof(*(this->cardsOwned->cards));

    Card ** cards = this->cardsOwned->cards;

    for(int i=0; i < numberOfCards; i++){ // 
       if(this->cardsOwned->cards[1][i].type== "Bomb"){
             orders.addOrder(new Bomb());
         }
         else if(this->cardsOwned->cards[1][i].type == "Blockade"){
             orders.addOrder(new Blockade());
         }
         else if(this->cardsOwned->cards[1][i].type == "Airlift"){
             orders.addOrder(new Airlift());
         }
        else if(this->cardsOwned->cards[1][i].type == "Negotiate"){
                orders.addOrder(new Negotiate());
        }
    }
    
}

// Stream operators
ostream& operator<<(ostream& os, const Player& other) {
    return os;
}

bool Player::operator==(const Player& other) {
    return true;
}

#endif
