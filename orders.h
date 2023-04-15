#pragma once
#include<iostream>
#include<vector> 
#include<iomanip>
#include<string> 



using namespace std;

class Player;
class Territory;

//abstract order class, can be overritten by subclasses
class Order //: public ILoggable, public Subject
{
public:
    Order();
    explicit Order(Player &);
    virtual ~Order() = 0;
    virtual bool validate() const = 0;
    virtual void execute() = 0; //pure virtual method
    virtual string getType() const = 0;
    virtual ostream& printOrder(ostream&) const;
    Player *currentPlayer;

    //string stringToLog() const override;

    //static LogObserver* orderLogger;
    //static void setOrderLogger(LogObserver* input);

    bool hasSegmentationFault() const;

private:
    virtual Order* clone() const = 0;
    friend ostream& operator<<(ostream& os, const Order& order);
    friend class OrdersList;
};

class Deploy : public Order
{
public:
    Deploy();
    Deploy(Territory &, Player *, int); // Target territory, current player, amount
    ~Deploy(); //destructor
    string getType() const override; //returns order type
    bool validate() const override; //returns true if valid
    virtual void execute(); //executes if valid

private:
    const static string type;
    Order* clone() const override; //copy constructor
    ostream& printOrder(ostream&) const override; //prints order
    Territory *target; // Target territory to deploy at
    int *amount; // Amount of armies to deploy
};


class Advance : public Order
{
public:
    Advance();
    Advance(Territory &, Territory &, Player *, int); // Src, dest, current player, amount
    ~Advance();
    string getType() const override;
    bool validate() const override;
    virtual void execute();

    bool hasSegmentationFault() const;

private:
    const static string type;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
    MapLoader *map;
    Territory *source;
    Territory *target;
    int *amount;
};

class Bomb : public Order
{
public:
    Bomb();
    Bomb(Territory &, Player *); // Target territory to bomb, current player
    ~Bomb();
    string getType() const override;
    bool validate() const override;
    virtual void execute();

private:
    const static string type;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
    Territory *target;
};

class Blockade : public Order
{
public:
    Blockade();
    Blockade(Territory &, Player *); // Target, current player
    ~Blockade();
    string getType() const override;
    bool validate() const override;
    virtual void execute();

private:
    const static string type;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
    Territory *target;
};

class Airlift : public Order
{
public:
    Airlift();
    Airlift(Territory &, Territory &, Player *, int); // Source, target, current player, amount
    ~Airlift();
    string getType() const override;
    bool validate() const override;
    virtual void execute();

private:
    const static string type;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
    Territory *source;
    Territory *target;
    int *amount;
};

class Negotiate : public Order
{
public:
    Negotiate();
    Negotiate(Player *, Player *);
    ~Negotiate();
    string getType() const override;
    bool validate() const override;
    virtual void execute();

private:
    const static string type;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
    Player *targetPlayer;
};

//creates an order object from a string
class newOrder
{
public:
    Order* createOrder(string) const;
};

class OrdersList //: public ILoggable, public Subject
{
public:
    OrdersList(); //default constructor
    ~OrdersList(); //destructor
    OrdersList(const OrdersList&); //copy constructor
    void addOrder(Order* o); 
    void remove(int); //removes Object based on pos
    void move(int, int); //takes pos1 and pos2 and switches objects
    void executeOrders(); //validates order and executes them
    vector<Order*> getOrders() const { return orders; }

    bool hasSegmentationFault() const;

   // string stringToLog() const override;

private:
    vector<Order*> orders;

    friend ostream& operator<<(ostream& os, const OrdersList& order);
};

void printOrders(const vector<Order*> &order_list);