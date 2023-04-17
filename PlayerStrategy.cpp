
#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <set>
#include <algorithm>
#include "Player.h"

#include <iostream>

using namespace std;

// issue order
void HumanPlayerStrategy::issueOrder(Player *player, MapLoader currentMap, Deck *deck, int numTerritoriesPerPlayer)
{
    // // Print out territories owned
    cout << "You are in the human issue order method" << endl;
    cout << "Territories owned: \n";
    cout << player->playername << " owns: ";
    cout << player->territoriesOwned.size() << " territories. \n";
    // Print out territories owned
    for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
    {
        if (currentMap.GetMap().GetTerritories().at(i)->GetOwner() == player->playername)
        {
            cout << currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName() << " ";
        }
    }
    cout << "\n";

    int numTroopsRemaining = player->reinforcementPool;

    // Creating Deploy Orders
    cout << "Choose a territory to defend:"
         << "\n";
    while (true)
    {
        string territoryToDefend;
        cin >> territoryToDefend;
        for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
        {
            if (territoryToDefend == currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName() && currentMap.GetMap().GetTerritories().at(i)->GetOwner() == player->playername)
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
                    Order *deployOrder = new Deploy(*currentMap.GetMap().GetTerritories()[i], player, numTroopsToDeploy);
                    player->ordersList.addOrder(deployOrder);
                    cout << "Added deploy order of " << numTroopsToDeploy << " armies on " << territoryToDefend << " to orders list."
                         << "\n";
                    player->defenseList.push_back(territoryToDefend);
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
            for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
            {
                if (currentMap.GetMap().GetTerritories().at(i)->GetOwner() == player->playername)
                {
                    cout << currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName() << " ";
                }
            }
            cout << "\n";
            string territoryToAdvanceFromName;
            cin >> territoryToAdvanceFromName;
            for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
            {
                if (territoryToAdvanceFromName == currentMap.GetMap().GetTerritories()[i]->GetTerritoryName())
                {
                    index1 = i;
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
                    // territoryToAdvanceTo = *currentMap.GetMap().GetTerritories().at(i);
                    break;
                }
            }
            bool attack = true;
            // Check if territory is owned by player to determine if we need to add it to the attack or defense list
            for (int i = 0; i < player->territoriesOwned.size(); i++)
            {
                if (territoryToAdvanceToName == player->territoriesOwned.at(i).GetTerritoryName())
                {
                    attack = false;
                }
            }
            if (attack == true)
            {
                player->attackList.push_back(territoryToAdvanceToName);
            }
            else
            {
                player->defenseList.push_back(territoryToAdvanceToName);
            }
            cout << "How many armies would you like to advance?"
                 << "\n";
            int numTroopsToAdvance;
            cin >> numTroopsToAdvance;

            Order *advanceOrder = new Advance(*currentMap.GetMap().GetTerritories().at(index1), *currentMap.GetMap().GetTerritories().at(index2), player, numTroopsToAdvance);
            player->ordersList.addOrder(advanceOrder);

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

        cout << "You have " << player->cardsOwned->size << " cards in your hand."
             << "\n";
        if (player->cardsOwned->size == 0)
        {
            cout << "You have no cards to play."
                 << "\n";
        }
        else
        {
            cout << "Cards in hand: "
                 << "\n";
            for (int i = 0; i < player->cardsOwned->size; i++)
            {
                cout << player->cardsOwned->cards[i]->type << ", ";
            }
            cout << "\n";
            while (true)
            {
                string cardToPlay;
                cin >> cardToPlay;
                bool cardFound = false;
                for (int i = 0; i < player->cardsOwned->size; i++)
                {
                    if (cardToPlay == player->cardsOwned->cards[i]->type)
                    {
                        cardFound = true;
                        player->cardsOwned->cards[i]->play(player->cardsOwned, deck, player);

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
                            player->ordersList.addOrder(new Blockade());
                        }
                        else if (cardToPlay == "Airlift")
                        {
                            cout << "Airlift Card Played" << endl;
                            player->ordersList.addOrder(new Airlift());
                        }
                        else if (cardToPlay == "Diplomacy")
                        {
                            cout << "Diplomacy Card Played" << endl;
                            player->ordersList.addOrder(new Negotiate());
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
}

void AggressivePlayerStrategy::issueOrder(Player *player, MapLoader currentMap, Deck *deck, int numTerritoriesPerPlayer)
{
    cout << "Aggressive Player Turn: " << endl;

    // find first territory that belongs to the player
    int indexOfStrongestTerritory = 0;
    for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
    {
        if (currentMap.GetMap().GetTerritories().at(i)->GetOwner() == player->playername)
        {
            indexOfStrongestTerritory = i;
            break;
        }
    }

    // Find the strongest territory that is owned by the player and that is not landlocked
    vector<Territory> adjEnemyTerritories;
    for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
    {
        // check if territory is owned by player
        vector<Territory> adjEnemyTerrTemp;
        if (currentMap.GetMap().GetTerritories().at(i)->GetOwner() == player->playername)
        {
            // check if the territory has more armies than current strongest territory
            if (currentMap.GetMap().GetTerritories().at(i)->GetArmyQuantity() >= currentMap.GetMap().GetTerritories().at(indexOfStrongestTerritory)->GetArmyQuantity())
            {

                // get all adjacent territories
                vector<Territory> adjTerritories = currentMap.GetMap().GetConnections(*currentMap.GetMap().GetTerritories().at(indexOfStrongestTerritory));

                for (int j = 0; j < adjTerritories.size(); j++)
                {
                    // check if the adjacent territory is not owned by player
                    if (!(adjTerritories[j].GetOwner() == player->playername))
                    {
                        adjEnemyTerrTemp.push_back(adjTerritories[j]);
                    }
                }

                // check if the territory has enemy adjacent territories (landlocked)
                if (adjEnemyTerrTemp.size() > 0)
                {
                    cout << "Enemy territories: ";
                    for (int k = 0; k < adjEnemyTerrTemp.size(); k++)
                    {
                        cout << adjEnemyTerrTemp[k].GetTerritoryName() << ", ";
                    }
                    cout << endl;

                    indexOfStrongestTerritory = i;
                    adjEnemyTerritories = adjEnemyTerrTemp;

                    cout << currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName() << " is the strongest territory with " << currentMap.GetMap().GetTerritories().at(i)->GetArmyQuantity() << " armies." << endl;
                }
            }
        }
    }

    cout << "The strongest territory is " << currentMap.GetMap().GetTerritories().at(indexOfStrongestTerritory)->GetTerritoryName() << endl;

    // Deploy all armies in the Player's reinforcement pool to the strongest territory
    cout << "Deploying all armies in the Player's reinforcement pool to the strongest territory" << endl;
    if (player->reinforcementPool > 0)
    {
        Deploy *deployOrder = new Deploy(*currentMap.GetMap().GetTerritories().at(indexOfStrongestTerritory), player, player->reinforcementPool);
        player->ordersList.addOrder(deployOrder);
    }

    // Fortify the strongest territory with all armies from all other territories
    cout << "Fortifying the strongest territory with all armies from all other territories" << endl;
    for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
    {
        if (currentMap.GetMap().GetTerritories().at(i)->GetOwner() == player->playername && i != indexOfStrongestTerritory)
        {
            if (currentMap.GetMap().GetTerritories().at(i)->GetArmyQuantity() > 0)
            {
                Advance *fortifyOrder = new Advance(*currentMap.GetMap().GetTerritories().at(i), *currentMap.GetMap().GetTerritories().at(indexOfStrongestTerritory), player, currentMap.GetMap().GetTerritories().at(i)->GetArmyQuantity());
                player->ordersList.addOrder(fortifyOrder);
            }
        }
    }
    cout << "Fortification complete" << endl;
    // Find all adjacent territories to advance to

    int numArmiesToAdvance = (currentMap.GetMap().GetTerritories().at(indexOfStrongestTerritory)->GetArmyQuantity()) / adjEnemyTerritories.size();
    // Create advance orders from the strongest territory to all adjacent territories
    cout << "Issuing advance orders from the strongest territory to all adjacent territories" << endl;
    for (int i = 0; i < adjEnemyTerritories.size(); i++)
    {
        // if(adjacentTerritories.at(i).GetOwner() == player->playername){
        cout << "Adding advance order on " << adjEnemyTerritories.at(i).GetTerritoryName() << " to orders list" << endl;
        for (int j = 0; j < currentMap.GetMap().GetTerritories().size(); j++)
        {
            if (currentMap.GetMap().GetTerritories().at(j)->GetTerritoryName() == adjEnemyTerritories.at(i).GetTerritoryName())
            {
                player->ordersList.addOrder(new Advance(*currentMap.GetMap().GetTerritories().at(indexOfStrongestTerritory), *currentMap.GetMap().GetTerritories().at(j), player, numArmiesToAdvance));
            }
        }
    }
}

void BenevolentPlayerStrategy::issueOrder(Player *player, MapLoader currentMap, Deck *deck, int numTerritoriesPerPlayer)
{
    cout << "you are in the benevolent issue order method" << endl;
    int leastArmies = 1000;

    // Find the territory with the least armies
    for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
    {
        // check if territory belongs to player
        if (currentMap.GetMap().GetTerritories().at(i)->GetOwner() == player->playername)
        {
            // check if territory has less armies than prev weakest territory
            if (currentMap.GetMap().GetTerritories().at(i)->GetArmyQuantity() < leastArmies)
            {
                leastArmies = currentMap.GetMap().GetTerritories().at(i)->GetArmyQuantity();
            }
        }
    }
    cout << "Least armies: " << leastArmies << endl;
    int numWithLeastArmies = 0;
    vector<Territory> territoriesWithLeastArmies;

    // Make a vector of the territories with the least armies
    cout << "Territories with the least armies: " << endl;
    for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
    {
        if (currentMap.GetMap().GetTerritories().at(i)->GetOwner() == player->playername)
        {
            if (currentMap.GetMap().GetTerritories().at(i)->GetArmyQuantity() == leastArmies)
            {
                numWithLeastArmies++;
                cout << currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName() << " ";
            }
        }
    }
    cout << endl;
    int armiesToDeploy = player->reinforcementPool;
    cout << "Armies to deploy: " << armiesToDeploy << endl;
    int armiesPerTerritory = floor(armiesToDeploy / numWithLeastArmies);
    int armiesLeftOver = armiesToDeploy % numWithLeastArmies;
    // Deploy reinforcement pool to territories with the least armies
    for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
    {
        if (currentMap.GetMap().GetTerritories().at(i)->GetOwner() == player->playername)
        {
            if (currentMap.GetMap().GetTerritories().at(i)->GetArmyQuantity() == leastArmies)
            {
                // territoriesWithLeastArmies.push_back(*currentMap.GetMap().GetTerritories().at(i));
                Deploy *deployOrder = new Deploy(*currentMap.GetMap().GetTerritories().at(i), player, armiesPerTerritory);
                player->ordersList.addOrder(deployOrder);
                cout << "Deploying " << armiesPerTerritory << " armies to " << currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName() << endl;
                if (armiesLeftOver > 0)
                {
                    Deploy *deployOrder = new Deploy(*currentMap.GetMap().GetTerritories().at(i), player, 1);
                    player->ordersList.addOrder(deployOrder);
                    armiesLeftOver--;
                    cout << "Deploying 1 army to " << currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName() << endl;
                }
            }
        }
    }
}
void NeutralPlayerStrategy::issueOrder(Player *player, MapLoader currentMap, Deck *deck, int numTerritoriesPerPlayer)
{
    cout << "you are in the neutral issue order method" << endl;

    int territoriesOwned = 0;
    for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
    {
        if (currentMap.GetMap().GetTerritories().at(i)->GetOwner() == player->playername)
        {
            territoriesOwned++;
        }
    }
    if (numTerritoriesPerPlayer > territoriesOwned)
    {
        cout << "Player " << player->playername << " is now an Aggressive Player" << endl;
        player->strategy = new AggressivePlayerStrategy(); // change strategy to aggressive
    }
}
void CheaterPlayerStrategy::issueOrder(Player *player, MapLoader currentMap, Deck *deck, int numTerritoriesPerPlayer)
{
    // Right idea but a lot of errors rn

    vector<Territory> adjacentTerritories;
    for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
    {
        if (currentMap.GetMap().GetTerritories().at(i)->GetOwner() == player->playername)
        {
            vector<Territory> newAdjTerritories = currentMap.GetMap().GetConnections(*currentMap.GetMap().GetTerritories().at(i));
            for (int j = 0; j < newAdjTerritories.size(); j++)
            {
                adjacentTerritories.push_back(newAdjTerritories[j]);
            }
        }
    }
    for (int i = 0; i < adjacentTerritories.size(); i++)
    {
        cout << adjacentTerritories[i].GetTerritoryName() << endl;
    }
    // remove duplicates
    for (int i = 0; i < currentMap.GetMap().GetTerritories().size(); i++)
    {
        if (currentMap.GetMap().GetTerritories().at(i)->GetOwner() == player->playername)
        {
            for (int j = 0; j < adjacentTerritories.size(); j++)
            {
                if (currentMap.GetMap().GetTerritories().at(i)->GetTerritoryName() == adjacentTerritories.at(j).GetTerritoryName())
                {
                    adjacentTerritories.erase(adjacentTerritories.begin() + j);
                }
            }
        }
    }
    cout << "---------------------------------------------" << endl;
    for (int i = 0; i < adjacentTerritories.size(); i++)
    {
        cout << adjacentTerritories[i].GetTerritoryName() << endl;
    }
    // Set all adjacent territories to player
    for (int i = 0; i < adjacentTerritories.size(); i++)
    {
        for (int j = 0; j < currentMap.GetMap().GetTerritories().size(); j++)
        {
            if (adjacentTerritories.at(i).GetTerritoryName() == currentMap.GetMap().GetTerritories().at(j)->GetTerritoryName() && (!(currentMap.GetMap().GetTerritories().at(j)->GetOwner() == player->playername)))
            {
                currentMap.GetMap().GetTerritories().at(j)->SetOwner(*player);
                cout << "Setting " << currentMap.GetMap().GetTerritories().at(j)->GetTerritoryName() << " to " << player->playername << endl;
            }
        }
    }

    // set<Territory> adjacentTerritoriesSet(adjacentTerritories.begin(), adjacentTerritories.end());

    // for(Territory t: adjacentTerritoriesSet){
    //     t.SetOwner(*player);
    // }
    cout << "you are in the cheater issue order method" << endl;
}

// attack methods
vector<string> HumanPlayerStrategy::toAttack(Player *player)
{
    cout << "you are in the human attack method" << endl;
    return player->toAttack();
}
vector<string> AggressivePlayerStrategy::toAttack(Player *player)
{
    cout << "you are in the aggressive attack method" << endl;
    return player->toAttack();
}
vector<string> BenevolentPlayerStrategy::toAttack(Player *player)
{
    cout << "you are in the benevolent attack method" << endl;
    return player->toAttack();
}
vector<string> NeutralPlayerStrategy::toAttack(Player *player)
{
    cout << "you are in the neutral attack method" << endl;
    return player->toAttack();
}
vector<string> CheaterPlayerStrategy::toAttack(Player *player)
{
    cout << "you are in the cheater attack method" << endl;
    return player->toAttack();
}

// defend methods
vector<string> HumanPlayerStrategy::toDefend(Player *player)
{
    cout << "you are in the human defend method" << endl;
    return player->toDefend();
}
vector<string> AggressivePlayerStrategy::toDefend(Player *player)
{
    cout << "you are in the aggressive defend method" << endl;
    return player->toDefend();
}
vector<string> BenevolentPlayerStrategy::toDefend(Player *player)
{
    cout << "you are in the benevolent defend method" << endl;
    return player->toDefend();
}
vector<string> NeutralPlayerStrategy::toDefend(Player *player)
{
    cout << "you are in the neutral defend method" << endl;
    return player->toDefend();
}
vector<string> CheaterPlayerStrategy::toDefend(Player *player)
{
    cout << "you are in the cheater defend method" << endl;
    return player->toDefend();
}
