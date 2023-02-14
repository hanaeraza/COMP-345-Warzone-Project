#include<iostream>
#include<vector> 
#include<iomanip>
#include<string> 
using namespace std;

//abstract order class
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
    ~Deploy();
    string getType() const override;
    bool validate() const override;
    void execute() const override;

private:
    const static string type;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
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

class newOrder
{
public:
    Order* createOrder(string) const;
};

class OrdersList
{
public:
    OrdersList();
    ~OrdersList();
    OrdersList(const OrdersList&);
    void addOrder(Order* o);
    void remove(int);
    void move(int, int);
    void executeOrders();
    OrdersList& operator=(const OrdersList&);
    vector<Order*> getOrders() const { return orders; }

private:
    vector<Order*> orders;

    friend ostream& operator<<(ostream&, const OrdersList&);
};

void printOrders(const vector<Order*> &order_list);