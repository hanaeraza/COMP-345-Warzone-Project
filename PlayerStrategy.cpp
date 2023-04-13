
#include "Player.h"
#include <iostream>

using namespace std; 


// issue order
void HumanPlayerStrategy::issueOrder(MapLoader currentMap, Deck *deck) {
     // Print out territories owned
    //      cout << "you are in the human issue order method" << endl; 
    // cout << "Territories owned: \n";
    // cout << this->player->playername << " owns: ";
    // cout << this->player->territoriesOwned.size() << " territories. \n";
    // for (int i = 0; i < this->player->territoriesOwned.size(); i++)
    // {
    //     cout << this->player->territoriesOwned.at(i).GetTerritoryName() << " ";
    // }
    // cout << "\n";

    // int numTroopsRemaining = this->player->reinforcementPool;

    // // Creating Deploy Orders
    // cout << "Choose a territory to defend:"
    //      << "\n";
    // while (true)
    // {
    //     string territoryToDefend;
    //     cin >> territoryToDefend;
    //     for (int i = 0; i < this->player->territoriesOwned.size(); i++)
    //     {
    //         if (territoryToDefend == this->player->territoriesOwned.at(i).GetTerritoryName())
    //         {
    //             cout << "How many armies would you like to deploy in " + player->territoriesOwned.at(i).GetTerritoryName() << "\n";
    //             cout << "You have " << this->player->reinforcementPool << " armies remaining to deploy."
    //                  << "\n";
    //             int numTroopsToDeploy;
    //             cin >> numTroopsToDeploy;
    //             if (numTroopsToDeploy < 1)
    //             {
    //                 cout << "You must deploy at least 1 troop. Please try again."
    //                      << "\n";
    //             }
    //             else if (numTroopsToDeploy > this->player->reinforcementPool)
    //             {
    //                 cout << "You do not have enough troops to deploy that many. Please try again."
    //                      << "\n";
    //             }

    //             else
    //             {
    //                 Order *deployOrder = new Deploy(this->player->territoriesOwned.at(i), this->player, numTroopsToDeploy);
    //                 this->player->ordersList.addOrder(deployOrder);
    //                 cout << "Added deploy order of " << numTroopsToDeploy << " armies on " << territoryToDefend << " to orders list."
    //                      << "\n";
    //                 this->player->defenseList.push_back(territoryToDefend);
    //                 this->player->reinforcementPool = this->player->reinforcementPool - numTroopsToDeploy;
    //             }
    //         }
    //     }
    //     if (this->player->reinforcementPool == 0)
    //     {
    //         cout << "You have deployed all your troops."
    //              << "\n";
    //         break;
    //     }
    //     else
    //     {
    //         cout << "Choose another territory to defend:"
    //              << "\n";
    //     }
    // }

    // // Creating Advance Orders

    // cout << "ADVANCE PHASE: "
    //      << "\n";
    // while (true)
    // {
    //     cout << "Do you want to issue an Advance Order? (y/n)"
    //          << "\n";
    //     string answer;
    //     cin >> answer;
    //     if (answer == "n")
    //     {
    //         break;
    //     }
    //     else if (answer == "y")
    //     {

    //         Territory territoryToAdvanceFrom;
    //         Territory territoryToAdvanceTo;
    //         cout << "Choose a Territory to Advance From:"
    //              << "\n";
    //         // Print out territories owned
    //         for (int i = 0; i < this->player->territoriesOwned.size(); i++)
    //         {
    //             cout << this->player->territoriesOwned.at(i).GetTerritoryName() << " ";
    //         }
    //         cout << "\n";
    //         string territoryToAdvanceFromName;
    //         cin >> territoryToAdvanceFromName;
    //         for (int i = 0; i < this->player->territoriesOwned.size(); i++)
    //         {
    //             if (territoryToAdvanceFromName == this->player->territoriesOwned.at(i).GetTerritoryName())
    //             {
    //                 territoryToAdvanceFrom = this->player->territoriesOwned.at(i);
    //                 break;
    //             }
    //         }
    //         cout << "Choose a Territory to Advance To:"
    //              << "\n";
    //         // Print out all territories
    //         for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
    //         {
    //             cout << currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName() << " ";
    //         }
    //         cout << "\n";
    //         string territoryToAdvanceToName;
    //         cin >> territoryToAdvanceToName;
    //         for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
    //         {
    //             if (territoryToAdvanceToName == currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName())
    //             {
    //                 territoryToAdvanceTo = *currentMap.GetMap().GetTerritories().at(i);
    //                 break;
    //             }
    //         }
    //         bool attack = true;
    //         // Check if territory is owned by player to determine if we need to add it to the attack or defense list
    //         for (int i = 0; i < this->player->territoriesOwned.size(); i++)
    //         {
    //             if (territoryToAdvanceToName == this->player->territoriesOwned.at(i).GetTerritoryName())
    //             {
    //                 attack = false;
    //             }
    //         }
    //         if (attack == true)
    //         {
    //             this->player->attackList.push_back(territoryToAdvanceToName);
    //         }
    //         else
    //         {
    //             this->player->defenseList.push_back(territoryToAdvanceToName);
    //         }
    //         cout << "How many armies would you like to advance?"
    //              << "\n";
    //         int numTroopsToAdvance;
    //         cin >> numTroopsToAdvance;
    //         this->player->ordersList.addOrder(new Advance(territoryToAdvanceFrom, territoryToAdvanceTo, this->player, numTroopsToAdvance));
    //         cout << "Added advance order of " << numTroopsToAdvance << " armies from " << territoryToAdvanceFrom.GetTerritoryName() << " to " << territoryToAdvanceTo.GetTerritoryName() << " to orders list."
    //              << "\n";
    //     }
    // }

    // /*The player uses one of the cards in their hand to issue an order that corresponds to the card in question. */
    // // add choose option

    // cout << "Choose a card to play:"
    //      << "\n";

    // cout << "You have " << this->player->cardsOwned->size << " cards in your hand."
    //      << "\n";
    // if (this->player->cardsOwned->size == 0)
    // {
    //     cout << "You have no cards to play."
    //          << "\n";
    // }
    // else
    // {
    //     cout << "Cards in hand: "
    //          << "\n";
    //     for (int i = 0; i < this->player->cardsOwned->size; i++)
    //     {
    //         cout << this->player->cardsOwned->cards[i]->type << ", ";
    //     }
    //     cout << "\n";
    //     while (true)
    //     {
    //         string cardToPlay;
    //         cin >> cardToPlay;
    //         bool cardFound = false;
    //         for (int i = 0; i < this->player->cardsOwned->size; i++)
    //         {
    //             if (cardToPlay == this->player->cardsOwned->cards[i]->type)
    //             {
    //                 cardFound = true;
    //                 this->player->cardsOwned->cards[i]->play(this->player->cardsOwned, deck, this->player);
    //                 if (this->player->cardsOwned->cards[i]->type == "Bomb")
    //                 {
    //                     string target;
    //                     cout << "Enter the name of the country you want to bomb: ";
    //                     cin >> target;
    //                     for(int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++){
    //                         if(currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName() == target){
    //                             cout << "Bomb Card Played" << endl;
    //                             //this->ordersList.addOrder(new Bomb(currentMap.GetMap().GetTerritories().at(i),this));
    //                             break;
    //                         }
    //                     }
    //                 }
    //                 else if (this->player->cardsOwned->cards[i]->type == "Blockade")
    //                 {
    //                     cout << "Blockade Card Played" << endl;
    //                     this->player->ordersList.addOrder(new Blockade());
    //                 }
    //                 else if (this->player->cardsOwned->cards[i]->type == "Airlift")
    //                 {
    //                     cout << "Airlift Card Played" << endl;
    //                     this->player->ordersList.addOrder(new Airlift());
    //                 }
    //                 else if (this->player->cardsOwned->cards[i]->type == "Diplomacy")
    //                 {
    //                     cout << "Diplomacy Card Played" << endl;
    //                     this->player->ordersList.addOrder(new Negotiate());
    //                 }
    //                 break;
    //             }
    //         }
    //         if (cardFound == false)
    //         {
    //             cout << "Card not found. Please try again."
    //                  << "\n";
    //         }
    //         else
    //         {
    //             break;
    //         }
    //     }
    // }

}
void AggressivePlayerStrategy::issueOrder(MapLoader currentMap, Deck *deck) {
    cout << "you are in the aggressive issue order method" << endl;
}
void BenevolentPlayerStrategy::issueOrder(MapLoader currentMap, Deck *deck) {
    cout << "you are in the benevolent issue order method" << endl;
}
void NeutralPlayerStrategy::issueOrder(MapLoader currentMap, Deck *deck) {
    cout << "you are in the neutral issue order method" << endl; 
}
void CheaterPlayerStrategy::issueOrder(MapLoader currentMap, Deck *deck) {
    cout << "you are in the cheater issue order method" << endl;
}

// attack methods
vector<string> HumanPlayerStrategy::toAttack() {
    cout << "you are in the human attack method" << endl;
    
}
vector<string>  AggressivePlayerStrategy::toAttack() {
    cout << "you are in the aggressive attack method" << endl;
}
vector<string> BenevolentPlayerStrategy::toAttack() {
    cout << "you are in the benevolent attack method" << endl;
}
vector<string> NeutralPlayerStrategy::toAttack() {
    cout << "you are in the neutral attack method" << endl;
}
vector<string> CheaterPlayerStrategy::toAttack() {
    cout << "you are in the cheater attack method" << endl;
}


// defend methods
vector<string> HumanPlayerStrategy::toDefend() {
    cout << "you are in the human defend method" << endl;
}
vector<string> AggressivePlayerStrategy::toDefend() {
    cout << "you are in the aggressive defend method" << endl;
}
vector<string> BenevolentPlayerStrategy::toDefend() {
    cout << "you are in the benevolent defend method" << endl;
}
vector<string> NeutralPlayerStrategy::toDefend() {
    cout << "you are in the neutral defend method" << endl;
}
vector<string> CheaterPlayerStrategy::toDefend() {
    cout << "you are in the cheater defend method" << endl;
    
}
