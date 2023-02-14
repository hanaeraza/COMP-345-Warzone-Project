#include "orders.h"
using namespace std;

int main() {


    newOrder orderCreate;  //
    OrdersList order_list; //creates an order list

    cout << "\nOrder List:" << endl;

    order_list.addOrder(orderCreate.createOrder("Diplomacy")); //Creates a new order object based on the string inputted. if order doesnt exists then nothing happens
    order_list.addOrder(orderCreate.createOrder("Advance"));
    order_list.addOrder(orderCreate.createOrder("Bomb"));
    order_list.addOrder(orderCreate.createOrder("Blockade"));
    order_list.addOrder(orderCreate.createOrder("Airlift"));
    order_list.addOrder(orderCreate.createOrder("Negotiate"));
    printOrders(order_list.getOrders());

    cout << "\nOrder List after swap:" << endl;
    order_list.move(2,1);
    printOrders(order_list.getOrders());

    cout << "\nOrder List after removal:" << endl;
    order_list.remove(1);
    printOrders(order_list.getOrders());
    
    order_list.executeOrders();
    
    return 0;
}