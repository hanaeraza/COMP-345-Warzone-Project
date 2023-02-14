#include "Orders.h"

//creates an order according to String
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
        //return new Order;
}

//default constructor
OrdersList::OrdersList() {}
//destructor /awdawdwadadawdawdad
OrdersList::~OrdersList()
{
    int listSize = orders.size();

    for (int i = 0; i < listSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete orders[i];
}

/**
 * Copy constructor: makes a deep copy of a list
 * @param oldList
 */
OrdersList::OrdersList(const OrdersList& oldList)
{
    int listSize = oldList.orders.size();
    orders = vector<Order*>(listSize);

    for (int i = 0; i < listSize; i++) // Same objects, but in different memory locations.
        orders[i] = oldList.orders[i]->clone();

}

/**
 * Method that adds an order to the orders vector
 * @param o
 */
void OrdersList::addOrder(Order* o)
{
    if (o == nullptr) // See OrdersFactory.
        cout << "Not a valid Order." << endl;
    else
    {
        orders.push_back(o);
    }
}

void OrdersList::remove(int pos)
{
    if (orders.size() == 0)
        cout << "Invalid Command. List is empty." << endl;
    else if (pos > orders.size() || pos < 1)
        cout << "Invalid Position." << endl;
    else
    {
        delete orders[pos - 1]; // Order objects are dynamically allocated, so frees memory.
        orders.erase(orders.begin() + pos - 1); // Once memory freed, delete actual pointer from list.
    }
}

void OrdersList::move(int pos1, int pos2)
{
    if (orders.size() == 0)
        cout << "Invalid Command. List is empty." << endl;
    else if (pos1 > orders.size() || pos2 > orders.size() || pos1 < 1 || pos2 < 1)
        cout << "Invalid Position." << endl;
    else
    {
        Order* temp = orders[pos1 - 1]; // Swap pointers. Address of actual object unchanged.
        orders[pos1 - 1] = orders[pos2 - 1];
        orders[pos2 - 1] = temp;
    }
}

//destructors
Order::~Order() {}
Deploy::~Deploy() {}
Advance::~Advance() {}
Bomb::~Bomb() {}
Blockade::~Blockade() {}
Airlift::~Airlift() {}
Negotiate::~Negotiate() {}

//goes through the 
void OrdersList::executeOrders()
{
    if (orders.size() == 0)
        cout << "No orders to execute." << endl;
    else
    {
        for (int i = 0; i < orders.size(); i++)
        {
            orders[i]->execute();
            delete orders[i];
        }
        orders.clear();
    }
}


OrdersList& OrdersList::operator=(const OrdersList& rhsList) // Releases resources by LHS and deep-copy
{                                                            // to RHS
    if (&rhsList == this) // Checks for self assignment
        return *this;

    int lhsListSize = orders.size();
    int rhsListSize = rhsList.orders.size();

    for (int i = 0; i < lhsListSize; i++)
        delete orders[i];

    orders = vector<Order*>(rhsListSize); // Reallocate memory for vector of size RHS

    for(int i = 0; i < rhsListSize; i++)
        orders[i] = rhsList.orders[i]->clone(); // Clone RHS element into LHS

    return *this;
}

//returns type of order
string Deploy::getType() const {return "Deploy"; }
string Advance::getType() const {return "Advance";}
string Bomb::getType() const {return "Bomb";}
string Blockade::getType() const {return "Blockade";}
string Airlift::getType() const {return "Airlift";}
string Negotiate::getType() const{return "Negotiate";}

//validate() methods (no use yet)
bool Deploy::validate() const
{
    cout << "Validating Deploy...\n";
    return true;
}

bool Advance::validate() const
{
    cout << "Validating Advance...\n";
    return true;
}

bool Bomb::validate() const
{
    cout << "Validating Bomb...\n";
    return true;
}

bool Blockade::validate() const
{
    cout << "Validating Blockade...\n";
    return true;
}

bool Airlift::validate() const
{
    cout << "Validating Airlift...\n";
    return true;
}

bool Negotiate::validate() const
{
    cout << "Validating Negotiate...\n";
    return true;
}

//if orders is valid then order is executed
void Deploy::execute() const
{
    if (validate())
        cout << "Executing Deploy...\n";
}

void Advance::execute() const
{
    if (validate())
        cout << "Executing Advance...\n";
}

void Bomb::execute() const
{
    if (validate())
        cout << "Executing Bomb...\n";
}

void Blockade::execute() const
{
    if (validate())
        cout << "Executing Blockade...\n";
}

void Airlift::execute() const
{
    if (validate())
        cout << "Executing Airlift...\n";
}

void Negotiate::execute() const
{
    if (validate())
        cout << "Executing Negotiate...\n";
}

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

/**
 * Since we have a list of pointers to an abstract class,
 * we need a way to polymorphically clone the objects in the
 * list if we ever decide to deep-copy the list. Calls the
 * compiler-generated copy constructor, which is OK since
 * these subclasses don't have object specific data members.
 * @return
 */
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