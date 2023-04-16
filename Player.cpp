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
    return this->defenseList;
    // return this->strategy->toDefend();
}

vector<string> Player::toAttack()
{
    return this->attackList;
    // return this->strategy->toAttack();
}

// Create an order object and add it to the player's list of orders
void Player::issueOrder(MapLoader currentMap, Deck *deck)
{
    // Print out territories owned
    cout << "Territories owned: \n";
    for (int i = 0; i < this->territoriesOwned.size(); i++)
    {
        cout << this->territoriesOwned.at(i).GetTerritoryName() << " ";
    }
    cout << "\n";

    int numTroopsRemaining = this->reinforcementPool;

    // Creating Deploy Orders
    cout << "Choose a territory to defend:"
         << "\n";
    while (true)
    {
        string territoryToDefend;
        cin >> territoryToDefend;
        for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
        {
            if (territoryToDefend == currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName())
            {
                cout << "How many armies would you like to deploy in " + currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName() << "\n";
                cout << "You have " << numTroopsRemaining << " armies remaining to deploy."
                     << "\n";
                int numTroopsToDeploy;
                cin >> numTroopsToDeploy;
                if (numTroopsToDeploy < 1)
                {
                    cout << "You must deploy at least 1 troop. Please try again."
                         << "\n";
                }
                else if (numTroopsToDeploy > numTroopsRemaining)
                {
                    cout << "You do not have enough troops to deploy that many. Please try again."
                         << "\n";
                }

                else
                {
                    Order *deployOrder = new Deploy(*currentMap.GetMap().GetTerritories()[i], this, numTroopsToDeploy);
                    this->ordersList.addOrder(deployOrder);
                    cout << "Added deploy order of " << numTroopsToDeploy << " armies on " << territoryToDefend << " to orders list."
                         << "\n";
                    this->defenseList.push_back(territoryToDefend);
                    numTroopsRemaining -= numTroopsToDeploy;
                }
            }
        }
        if (numTroopsRemaining == 0)
        {
            cout << "You have deployed all your troops."
                 << "\n";
            break;
        }
        else
        {
            cout << "Choose another territory to defend:"
                 << "\n";
        }
    }

    // Creating Advance Orders

    cout << "ADVANCE PHASE: "
         << "\n";
    while (true)
    {
        cout << "Do you want to issue an Advance Order? (y/n)"
             << "\n";
        string answer;
        cin >> answer;
        if (answer == "n")
        {
            break;
        }
        else if (answer == "y")
        {

            Territory territoryToAdvanceFrom;
            Territory territoryToAdvanceTo;
            int index1 = 0;
            int index2 = 0;
            cout << "Choose a Territory to Advance From:"
                 << "\n";
            // Print out territories owned
            for (int i = 0; i < this->territoriesOwned.size(); i++)
            {
                cout << this->territoriesOwned.at(i).GetTerritoryName() << " ";
            }
            cout << "\n";
            string territoryToAdvanceFromName;
            cin >> territoryToAdvanceFromName;
            for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
            {
                if (territoryToAdvanceFromName == currentMap.GetMap().GetTerritories()[i]->GetTerritoryName())
                {
                    index1 = i;
                    //territoryToAdvanceFrom = this->territoriesOwned.at(i);
                    // territoryToAdvanceFrom.SetOwner(*(this));
                    // for (int j = 0; j < currentMap.GetMap().GetTerritories().size(); j++)
                    // {
                    //     if (currentMap.GetMap().GetTerritories().at(j)->GetTerritoryName() == territoryToAdvanceFromName)
                    //     {
                    //         territoryToAdvanceFrom = *currentMap.GetMap().GetTerritories().at(j);
                    //     }
                    // }
                    break;
                }
            }
            cout << "Choose a Territory to Advance To:"
                 << "\n";
            // Print out all territories
            for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
            {
                cout << currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName() << " ";
            }
            cout << "\n";
            string territoryToAdvanceToName;
            cin >> territoryToAdvanceToName;
            for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
            {
                if (territoryToAdvanceToName == currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName())
                {
                    index2 = i;
                    //territoryToAdvanceTo = *currentMap.GetMap().GetTerritories().at(i);
                    break;
                }
            }
            bool attack = true;
            // Check if territory is owned by player to determine if we need to add it to the attack or defense list
            for (int i = 0; i < this->territoriesOwned.size(); i++)
            {
                if (territoryToAdvanceToName == this->territoriesOwned.at(i).GetTerritoryName())
                {
                    attack = false;
                }
            }
            if (attack == true)
            {
                this->attackList.push_back(territoryToAdvanceToName);
            }
            else
            {
                this->defenseList.push_back(territoryToAdvanceToName);
            }
            cout << "How many armies would you like to advance?"
                 << "\n";
            int numTroopsToAdvance;
            cin >> numTroopsToAdvance;
            
            Order *advanceOrder = new Advance(*currentMap.GetMap().GetTerritories().at(index1), *currentMap.GetMap().GetTerritories().at(index2), this, numTroopsToAdvance);
            this->ordersList.addOrder(advanceOrder);

            // advanceOrders.push_back(new Advance(territoryToAdvanceFrom, territoryToAdvanceTo, this, numTroopsToAdvance));
            // Record advance order information here in a new list
            cout << "Added advance order of " << numTroopsToAdvance << " armies from " << currentMap.GetMap().GetTerritories().at(index1)->GetTerritoryName() << " to " << currentMap.GetMap().GetTerritories().at(index2)->GetTerritoryName() << " to orders list."
                 << "\n";
        }
    }

    /*The player uses one of the cards in their hand to issue an order that corresponds to the card in question. */
    // add choose option

    cout << "Do you want to issue an order using a card? (y/n)"
         << "\n";
    string answer;
    cin >> answer;
    if (answer == "y")
    {
        cout << "Choose a card to play:"
             << "\n";

        cout << "You have " << this->cardsOwned->size << " cards in your hand."
             << "\n";
        if (this->cardsOwned->size == 0)
        {
            cout << "You have no cards to play."
                 << "\n";
        }
        else
        {
            cout << "Cards in hand: "
                 << "\n";
            for (int i = 0; i < this->cardsOwned->size; i++)
            {
                cout << this->cardsOwned->cards[i]->type << ", ";
            }
            cout << "\n";
            while (true)
            {
                string cardToPlay;
                cin >> cardToPlay;
                bool cardFound = false;
                for (int i = 0; i < this->cardsOwned->size; i++)
                {
                    if (cardToPlay == this->cardsOwned->cards[i]->type)
                    {
                        cardFound = true;
                        this->cardsOwned->cards[i]->play(this->cardsOwned, deck, this);

                        if (cardToPlay == "Bomb")
                        {
                            string target;
                            cout << "Enter the name of the country you want to bomb: ";
                            cin >> target;
                            for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
                            {
                                if (currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName() == target)
                                {
                                    cout << "Bomb Card Played" << endl;
                                    // this->ordersList.addOrder(new Bomb(currentMap.GetMap().GetTerritories().at(i),this));
                                    break;
                                }
                            }
                        }
                        else if (cardToPlay == "Blockade")
                        {
                            cout << "Blockade Card Played" << endl;
                            this->ordersList.addOrder(new Blockade());
                        }
                        else if (cardToPlay == "Airlift")
                        {
                            cout << "Airlift Card Played" << endl;
                            this->ordersList.addOrder(new Airlift());
                        }
                        else if (cardToPlay == "Diplomacy")
                        {
                            cout << "Diplomacy Card Played" << endl;
                            this->ordersList.addOrder(new Negotiate());
                        }
                        break;
                    }
                }
                if (cardFound == false)
                {
                    cout << "Card not found. Please try again."
                         << "\n";
                }
                else
                {
                    break;
                }
            }
        }
    }
    // this->strategy->issueOrder(currentMap, deck);
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