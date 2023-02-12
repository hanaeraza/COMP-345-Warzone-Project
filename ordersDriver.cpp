#include "orders.h"
using namespace std;

int main() {
    OrderList order_list;

    //creates the order objects
    Deploy Deploy;
    Advance Advance;
    Bomb Bomb;
    Blockade Blockade;
    Airlift Airlift;
    Negotiate Negotiate;

    //adds orders to orderlist and prints list
    order_list.addOrder(&Deploy);
    order_list.addOrder(&Advance);
    order_list.addOrder(&Bomb);
    order_list.addOrder(&Blockade);
    order_list.addOrder(&Airlift);
    order_list.addOrder(&Negotiate);
    order_list.printOrderList();

    //removes order and prints list
    std::cout << "\nRemoving Deploy order:" << std::endl;
    order_list.removeOrder(&Deploy);
    order_list.printOrderList();

    //moves order and prints list
    std::cout << "\nMoving Advance Order to Pos 5 and Blockade to Pos 1:" << std::endl;
    order_list.moveOrder(&Advance, 4);
    order_list.moveOrder(&Blockade, 0);
    order_list.printOrderList();

    return 0;
}