#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

//#include "LoggingObserver.h"
#include "Orders.h"
#include "Player.h"
#include "Map.h"

std::ostream& operator<<(std::ostream& os, const Order& order){
    os << "Order: " << order.getType() << "\n";
    return order.printOrder(os);
}
std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList){
    os << "Orders List: \n";
    for (int i = 0; i < ordersList.getOrders().size(); i++)
    {
        os << ordersList.getOrders()[i] << " " << i << "\n";
    }
    return os;
}

//LogObserver* Order::orderLogger = new LogObserver("log.txt");

//creates an order object according to string inputted
Order* newOrder::createOrder(string orderType) const
{
    if (orderType == "Deploy")
        return new Deploy;
    else if (orderType == "Advance")
        return new Advance;
    else if (orderType == "Bomb")
        return new Bomb;
    else if (orderType == "Blockade")
        return new Blockade;
    else if (orderType == "Airlift")
        return new Airlift;
    else if (orderType == "Negotiate")
        return new Negotiate;
    else
        return nullptr;
}

//--------[Order]---------

Order::Order() //default constructor
{
    // currentPlayer = nullptr;
}   
Order::Order(Player& currentPlayer) //parametized constructor
{
    this->currentPlayer = &currentPlayer;
}
Order::~Order() //destructor
{
    // currentPlayer = nullptr;
}

//--------[Deploy]---------
Deploy::Deploy() : Order() //default constructor
{
    target = nullptr;
    amount = nullptr;
}
Deploy::Deploy(Territory& target, Player* currentPlayer, int amount)//parametized constructor
{
    this->target = &target;
    this->currentPlayer = currentPlayer;
    int* copiedAmount = new int(amount);
    this->amount = copiedAmount;
}
Deploy::~Deploy() //destructor
{
    // target = nullptr;
    // currentPlayer = nullptr;
    // delete amount;
}

//--------[Advance]---------
Advance::Advance() : Order()
{
    source = nullptr;
    target = nullptr;
    amount = nullptr;
}
Advance::Advance(Territory& source, Territory& target, Player* currentPlayer, int amount) //parametized constructor
{
    this->source = &source;
    this->target = &target;
    this->currentPlayer = currentPlayer;
    int* copiedAmount = new int(amount);
    this->amount = copiedAmount;
}
Advance::~Advance() //destructor
{
    // source = nullptr;
    // target = nullptr;
    // delete amount;
}

//--------[Bomb]---------
Bomb::Bomb() : Order() //default constructor
{
    target = nullptr;
}
Bomb::Bomb(Territory& target, Player* currentPlayer) //parametized constructor
{
    this->target = &target;
    this->currentPlayer = currentPlayer;
}
Bomb::~Bomb() //destructor
{
    // target = nullptr;
}

//--------[Blockade]---------
Blockade::Blockade() : Order() //default constructor
{
    target = nullptr;
}
Blockade::Blockade(Territory& target, Player* currentPlayer)//parametized constructor
{
    this->target = &target;
    this->currentPlayer = currentPlayer;
}
Blockade::~Blockade() //destructor
{
    // target = nullptr;
}

//--------[Airlift]---------
Airlift::Airlift() : Order() //default constructor
{
    source = nullptr;
    target = nullptr;
    amount = nullptr;
}
Airlift::Airlift(Territory& source, Territory& target, Player* currentPlayer, int amount)//parametized constructor
{
    this->source = &source;
    this->target = &target;
    this->currentPlayer = currentPlayer;
    int* copiedAmount = new int(amount);
    this->amount = copiedAmount;
}
Airlift::~Airlift() //destructor
{
    // source = nullptr;
    // target = nullptr;
    // delete amount;
}

//--------[Negotiate]---------
Negotiate::Negotiate() : Order() //default constructor
{
    targetPlayer = nullptr;
}
Negotiate::Negotiate(Player* targetPlayer, Player* currentPlayer)//parametized constructor
{
    this->targetPlayer = targetPlayer;
    this->currentPlayer = currentPlayer;
}
Negotiate::~Negotiate() //destructor
{
    // targetPlayer = nullptr;
}




//copy constructors
Order* Deploy::clone() const
{
    return new Deploy(*this);
}

Order* Advance::clone() const
{
    return new Advance(*this);
}

Order* Bomb::clone() const
{
    return new Bomb(*this);
}

Order* Blockade::clone() const
{
    return new Blockade(*this);
}

Order* Airlift::clone() const
{
    return new Airlift(*this);
}

Order* Negotiate::clone() const
{
    return new Negotiate(*this);
}


//returns type of order
string Deploy::getType() const {return "Deploy"; }
string Advance::getType() const {return "Advance";}
string Bomb::getType() const {return "Bomb";}
string Blockade::getType() const {return "Blockade";}
string Airlift::getType() const {return "Airlift";}
string Negotiate::getType() const{return "Negotiate";}

//--------[OrderList]---------
OrdersList::OrdersList()  {
   //attach(Order::orderLogger);
} //default constructor
OrdersList::~OrdersList() //destructor
{
    for (auto order : orders) {
        delete order;
    }
}
OrdersList::OrdersList(const OrdersList& oldList) //copy constructor
{
    //attach(Order::orderLogger);
    orders = vector<Order*>(oldList.orders.size());

    for (int i = 0; i < oldList.orders.size(); i++)
        orders[i] = oldList.orders[i]->clone();
}


//adds order to list
void OrdersList::addOrder(Order* o)
{
    if (o == nullptr)
        cout << "Not a valid Order." << endl;
    else
    {
        orders.push_back(o);
        //notify(this);

        std::stringstream stream;
        stream << "Added To List: \n\t" << *o << "\n";
        //notify(stream.str());
    }
}

//removes order from list
void OrdersList::remove(int pos)
{
    if (orders.size() == 0)
        cout << "Invalid Command. List is empty." << endl;
    else if (pos > orders.size() || pos < 1)
        cout << "Invalid Position." << endl;
    else
    {
        delete orders[pos - 1];
        orders.erase(orders.begin() + pos - 1);
    }
}

//switches 2 orders from list
void OrdersList::move(int pos1, int pos2)
{
    if (orders.size() == 0)
        cout << "Invalid Command. List is empty." << endl;
    else if (pos1 > orders.size() || pos2 > orders.size() || pos1 < 1 || pos2 < 1)
        cout << "Invalid Position." << endl;
    else
    {
        Order* temp = orders[pos1 - 1];
        orders[pos1 - 1] = orders[pos2 - 1];
        orders[pos2 - 1] = temp;
    }
}

//goes through the order list and validates them, if validated then executes them
void OrdersList::executeOrders()
{
    if (orders.size() == 0)
        cout << "No orders to execute." << endl;
    else
    {
        //notify(this);
        for (int i = 0; i < orders.size(); i++)
        {
          
            orders[i]->execute();
            delete orders[i];
        }
        orders.clear();
    }
}

//validate() methods
bool Deploy::validate() const {

    //checks if territory is owned by player
    for (int i = 0; i < currentPlayer->territoriesOwned.size(); i++) {
        if (currentPlayer->territoriesOwned.at(i).GetTerritoryName() == target->GetTerritoryName()) {
            cout << currentPlayer->territoriesOwned.at(i).GetTerritoryName() << endl;
            //checks if the amount to deploy is greater than the reinforcement pool
            if (*amount >= currentPlayer->reinforcementPool) {
                cout << "Deploy order validated." << endl;
                currentPlayer->reinforcementPool -= *amount;
                return true;
            }
            else {
                cout << "Deploy not Validated: Not Enough Troops" << endl;
                return false;
            }
        }
    }

    cout << "Deploy not Validated: You do not own this territory." << endl;
    return false;

}
 bool Advance::hasSegmentationFault() const {
        // iterate through all the pointers in the object
        for (const Territory* ptr : {source, target}) {
            // check if the pointer is null
            if (ptr == nullptr) {
                return true;
            }

            // check if the pointer points to invalid memory
            try {
                Territory val = *ptr; // dereference the pointer
                (void)val; // suppress unused variable warning
            } catch (...) {
                return true;
            }
        }

        // no segmentation faults detected
        return false;
    }
bool Advance::validate() const
{


    //If the target territory is connected to the source territory, the order is invalid.
    // else if (!source->IsConnected(target))
    // {
    //     cout << "Advance not Validated: The target territory is not adjacent to the source territory.\n" << endl;
    //     return false;
    // }

    //checks if the amount is greater than the army in the territory
    // if (hasSegmentationFault()) {
    //     cout << "Advance not Validated: Segmentation Fault" << endl;
    //     return false;
    // }
    
    if (*amount > source->GetArmyQuantity())
    {
        cout << "Advance not Validated: You do not own this many armies in this territory." << endl;
        return false;
    }

    cout << "Advance order validated." << endl;
    return true;
}

bool Bomb::validate() const
{

    //checks if territory is owned by player
    for (int i = 0; i < currentPlayer->territoriesOwned.size(); i++) {
        if (currentPlayer->territoriesOwned.at(i).GetTerritoryName() == target->GetTerritoryName()) {
            cout << "Bomb not Validated: You cannot Bomb yourself." << endl;
            return false;
        }
    }

    //If the target territory is not connected to one of the territory owned by the player issuing the order, then the order is invalid. 
    // else if (!source->isConnected(target))
    // {
    //     cout << "Invalid Order: The target territory is not adjacent to the source territory.\n" << endl;
    //     return false;
    // }

    cout << "Bomb order validated." << endl;
    return true;
}

bool Blockade::validate() const
{

    //If the target territory belongs to an enemy player, the order is declared invalid. 
    //checks if territory is owned by player
    for (int i = 0; i < currentPlayer->territoriesOwned.size(); i++) {
        if (currentPlayer->territoriesOwned.at(i).GetTerritoryName() == target->GetTerritoryName()) {
            cout << "Blockade order validated." << endl;
            return true;
        }
    }

    cout << "Blockade not Validated: Select your own territory to Blockade." << endl;
    return false;
}

bool Airlift::validate() const
{
    //If the source does not belong to the player that issued the order, the order is invalid.
    //checks if territory is owned by player
    for (int i = 0; i < currentPlayer->territoriesOwned.size(); i++) {
        if (currentPlayer->territoriesOwned.at(i).GetTerritoryName() == source->GetTerritoryName()) {
            cout << "Blockade order validated." << endl;
            return true;
            if (*amount <= source->GetArmyQuantity()) {
                cout << "Airlift order validated." << endl;
                return true;
            }
            else {
                cout << "Airlift not Validated: You do not own this many armies in this territory." << endl;
                return false;
            }
        }
    }
    cout << "Airlift not Validated: Source territory does not belong to player." << endl;
    return false;

}

bool Negotiate::validate() const
{

    //If the target is the player issuing the order, then the order is invalid. 
    if(targetPlayer == currentPlayer)
    {
        cout << "Negotiate not Validated: You cannot negotiate with yourself." << endl;
        return false;
    }

    cout << "Negotiate order validated." << endl;
    return true;
}

//if orders is valid then order is executed
void Deploy::execute()
{
    if (validate()) {
        target->SetArmyQuantity(*amount + target->GetArmyQuantity());
        cout << target->GetArmyQuantity() << endl;
        cout << "Deploy order of " << *amount << " armies on " << target->GetTerritoryName() << endl;
        cout << target->GetTerritoryName() << " now has " << target->GetArmyQuantity() << " armies." << endl;
    }
}

void Advance::execute()
{
    if (validate()) {
        //if territory belongs to player then move armies
        if (source->GetOwner() == target->GetOwner())
        {
            source->SetArmyQuantity(source->GetArmyQuantity() - *amount);
            target->SetArmyQuantity(target->GetArmyQuantity() + *amount);
        }

        //if moving troops to enemy territory then its an attack
        else
        {
            //Calculate the number of attacking units that will be killed
            int attackingKills = 0;
            for (int i = 0; i < source->GetArmyQuantity(); i++) {
                double roll = (double) rand() / RAND_MAX; // generate random number between 0 and 1
                if (roll <= 0.6) {
                attackingKills++;
                }
            }

            //Calculate the number of defending units that will be killed
            int defendingKills = 0;
            for (int i = 0; i < target->GetArmyQuantity(); i++) {
                double roll = (double) rand() / RAND_MAX; // generate random number between 0 and 1
                if (roll <= 0.7) {
                    defendingKills++;
                }
            }

            //Update the armies in the territory
            if (defendingKills >= target->GetArmyQuantity()) {
                // attacker takes control of the territory
                target->SetOwner(source->GetOwner());
                source->SetArmyQuantity(source->GetArmyQuantity() - attackingKills);
            } else {
                target->SetArmyQuantity(target->GetArmyQuantity() - defendingKills);
            }

        }
        cout << "Advance Executed." << endl;
    }
}

void Bomb::execute()
{
    if (validate())
        target->SetArmyQuantity(target->GetArmyQuantity() / 2);
        cout << "Bomb Executed." << endl;
}

void Blockade::execute()
{
    if (validate())
    {
        target->SetArmyQuantity(target->GetArmyQuantity() * 2);
        //Missing neutral player
        cout << "Blockade Executed." << endl;
    }
}

void Airlift::execute()
{
    if (validate()) {

        if (source->GetOwner() == target->GetOwner()) // Transferring army to another territory
        {
            source->SetArmyQuantity(source->GetArmyQuantity() - *amount);
            target->SetArmyQuantity(target->GetArmyQuantity() + *amount);
        }

        //if its for an enemy territory then its an attack
        else
        {
            //Calculate the number of attacking units that will be killed
            int attackingKills = 0;
            for (int i = 0; i < source->GetArmyQuantity(); i++) {
                double roll = (double) rand() / RAND_MAX; // generate random number between 0 and 1
                if (roll <= 0.6) {
                attackingKills++;
                }
            }

            //Calculate the number of defending units that will be killed
            int defendingKills = 0;
            for (int i = 0; i < target->GetArmyQuantity(); i++) {
                double roll = (double) rand() / RAND_MAX; // generate random number between 0 and 1
                if (roll <= 0.7) {
                    defendingKills++;
                }
            }

            //Update the armies in the territory
            if (defendingKills >= target->GetArmyQuantity()) {
                // attacker takes control of the territory
                target->SetOwner(source->GetOwner());
                source->SetArmyQuantity(source->GetArmyQuantity() - attackingKills);
            } else {
                target->SetArmyQuantity(target->GetArmyQuantity() - defendingKills);
            }

        }

        cout << "Airlift executed." << endl;
    }
}

void Negotiate::execute()
{
    if (validate())
    {
        // cout << "Negotiate is being executed!\n";
        // currentPlayer->alliedTo(targetPlayer);
        // targetPlayer->alliedTo(currentPlayer);
        //cout << "Negotiate has finished executing!" << endl;
    }
}

//loops through the order list and calls printOrder which prints the orders
void printOrders(const std::vector<Order*>& orders) {
  int index = 0;
  for (const auto& order : orders) {
    std::cout << index+1 << ": ";
    order->printOrder(std::cout);
    std::cout << std::endl;
    ++index;
  }
}

ostream& Deploy::printOrder(ostream& out) const
{
    return out << "Deploy";
}

ostream& Advance::printOrder(ostream& out) const
{
    return out << "Advance";
}

ostream& Bomb::printOrder(ostream& out) const
{
    return out << "Bomb";
}

ostream& Blockade::printOrder(ostream& out) const
{
    return out << "Blockade";
}

ostream& Airlift::printOrder(ostream& out) const
{
    return out << "Airlift";
}

ostream& Negotiate::printOrder(ostream& out) const
{
    return out << "Negotiate";
}

ostream& Order::printOrder(ostream& out) const
{
    return out << "Order";
}

// string Order::stringToLog() const
// {
//     stringstream stream;
//     string output;
//     stream << *this;
//     output = stream.str();
//     return output;
// }

// string OrdersList::stringToLog() const
// {
//     stringstream stream;
//     string output;
//     stream << *this;
//     output = stream.str();
//     return output;
// }

// void Order::setOrderLogger(LogObserver* input){
//     delete orderLogger;
//     orderLogger = input;
// }

bool Order::hasSegmentationFault() const
{
    // iterate through all the pointers in the object
    for (const auto* ptr : {&currentPlayer}) {
        // check if the pointer is null
        if (ptr == nullptr) {
            return true;
        }

        // check if the pointer points to invalid memory
        try {
            auto val = ptr; // dereference the pointer
            (void)val; // suppress unused variable warning
        } catch (...) {
            return true;
        }
    }

    // no segmentation faults detected
    return false;
}

bool Advance::hasSegmentationFault() const
{
    // iterate through all the pointers in the object
    for (const auto* ptr : {&source, &target}) {
        // check if the pointer is null
        if (ptr == nullptr) {
            return true;
        }

        // check if the pointer points to invalid memory
        try {
            auto val = ptr; // dereference the pointer
            (void)val; // suppress unused variable warning
        } catch (...) {
            return true;
        }
    }

    // no segmentation faults detected
    return Order::hasSegmentationFault();
}

bool OrdersList::hasSegmentationFault() const
{
    for (int i = 0; i < orders.size(); i++) {
        if (orders[i]->hasSegmentationFault()) {
            return true;
        }
    }

    // no segmentation faults detected
    return false;
}