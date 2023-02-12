#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Order
{
public :
	Order();
private :
}

class Deploy : public Order 
{
public:
	DeployOrder();
private:

};

class Advance : public Order {
public:
	Advance();

private:
};

class Bomb : public Order 
{
public:
	Bomb();

private:
};

class Blockade : public Order
{
public:
	Blockade();
private:
};

class Airlift : public Order
{
public:
	Airlift();
private:
};

class Negotiate : public Order
{
public:
	Negotiate();

private:
};

class OrderList
{
public:
  OrderList();
  ~OrderList();
  void addOrder(Order* order);
  void removeOrder(Order* order);
  void moveOrder(Order* order, int new_index);
  void printOrder();
private:
  vector<Order*> vec_order_list;
};