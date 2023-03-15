#pragma once
#include<iostream>
#include<vector> 
#include<iomanip>
#include<string> 
using namespace std;

//abstract order class, can be overritten by subclasses
class Order
{
public:
    virtual ~Order() = 0;
    virtual bool validate() const = 0;
    virtual void execute() const = 0;
    virtual string getType() const = 0;
    virtual ostream& printOrder(ostream&) const = 0;

private:
    virtual Order* clone() const = 0;
    friend ostream& operator<<(ostream&, const Order&);
    friend class OrdersList;
    
};

class Deploy : public Order
{
public:
    ~Deploy(); //destructor
    string getType() const override; //returns order type
    bool validate() const override; //returns true if valid
    void execute() const override; //executes if valid

private:
    const static string type;
    Order* clone() const override; //copy constructor
    ostream& printOrder(ostream&) const override; //prints order
};


class Advance : public Order
{
public:
    ~Advance();
    string getType() const override;
    bool validate() const override;
    void execute() const override;

private:
    const static string type;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
};

class Bomb : public Order
{
public:
    ~Bomb();
    string getType() const override;
    bool validate() const override;
    void execute() const override;

private:
    const static string type;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
};

class Blockade : public Order
{
public:
    ~Blockade();
    string getType() const override;
    bool validate() const override;
    void execute() const override;

private:
    const static string type;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
};

class Airlift : public Order
{
public:
    string getType() const override;
    bool validate() const override;
    void execute() const override;
    ~Airlift();

private:
    const static string type;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
};

class Negotiate : public Order
{
public:
    ~Negotiate();
    string getType() const override;
    bool validate() const override;
    void execute() const override;

private:
    const static string type;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
};

//creates an order object from a string
class newOrder
{
public:
    Order* createOrder(string) const;
};

class OrdersList
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

private:
    vector<Order*> orders;

    friend ostream& operator<<(ostream&, const OrdersList&);
};

void printOrders(const vector<Order*> &order_list);