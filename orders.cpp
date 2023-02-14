#include "Orders.h"

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

//destructors
Order::~Order() {}
Deploy::~Deploy() {}
Advance::~Advance() {}
Bomb::~Bomb() {}
Blockade::~Blockade() {}
Airlift::~Airlift() {}
Negotiate::~Negotiate() {}

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

//default constructor
OrdersList::OrdersList() {}
//destructor
OrdersList::~OrdersList()
{
    int listSize = orders.size();

    for (int i = 0; i < listSize; i++)
        delete orders[i];
}
//copy constructor
OrdersList::OrdersList(const OrdersList& oldList)
{
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
        for (int i = 0; i < orders.size(); i++)
        {
            orders[i]->execute();
            delete orders[i];
        }
        orders.clear();
    }
}

//validate() methods
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