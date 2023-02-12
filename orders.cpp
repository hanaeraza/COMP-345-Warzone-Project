#include "Orders.h"

// Order class implementation
Order()
{
}

Deploy :: Deploy()
{
    std::cout << "Creating Deploy...\n";
};

Advance :: Advance()
{
    std::cout << "Creating Advance...\n";
};

Bomb :: Bomb()
{
    std::cout << "Creating Bomb...\n";
};

Blockade :: Blockade()
{
    std::cout << "Creating Blockade...\n";

};

Airlift :: Airlift()
{
    std::cout << "Creating Airlift...\n";
};

Negotiate :: Negotiate()
{
    std::cout << "Creating Negotiate...\n";
};


Orderlist::~OrderList() {
     for (auto order : vec_order_list) {
         delete order;
    }
}

void Orderlist::addOrder(Order* order) {
    vec_order_list.push_back(order);
}

void Orderlist::removeOrder(Order* order) {
    auto it = std::find(vec_order_list.begin(), vec_order_list.end(), order);
    if (it != vec_order_list.end()) {
        vec_order_list.erase(it);
        delete order;
    }
}

void Orderlist::moveOrder(Order* order, int new_index) {
    auto it = std::find(vec_order_list.begin(), vec_order_list.end(), order);
    if (it != vec_order_list.end()) {
        vec_order_list.erase(it);
        vec_order_list.insert(vec_order_list.begin() + new_index, order);
    }
    
}

void Orderlist::printOrderList() const {
    std::cout << "\nOrder List:" << std::endl;
    for (int i = 0; i < vec_order_list.size(); i++) {
        Order* order = vec_order_list[i];
        if (dynamic_cast<DeployOrder*>(order) != nullptr) {
            std::cout << i + 1 << ". DeployOrder" << std::endl;
        } else if (dynamic_cast<AdvanceOrder*>(order) != nullptr) {
            std::cout << i + 1 << ". AdvanceOrder" << std::endl;
        } else if (dynamic_cast<BombOrder*>(order) != nullptr) {
            std::cout << i + 1 << ". BombOrder" << std::endl;
        } else if (dynamic_cast<BlockadeOrder*>(order) != nullptr) {
            std::cout << i + 1 << ". BlockadeOrder" << std::endl;
        } else if (dynamic_cast<AirliftOrder*>(order) != nullptr) {
            std::cout << i + 1 << ". AirliftOrder" << std::endl;
        } else if (dynamic_cast<NegotiateOrder*>(order) != nullptr) {
            std::cout << i + 1 << ". NegotiateOrder" << std::endl;
        }
    }
}

