#include "orders.h"
#include "player.h"
#include "card.h"
#include "map.h"
using namespace std;

class Player;
class Territory;

int main() {

    Hand* myHand = new Hand();
    vector<Territory>* myTerritories = new vector<Territory>();
    OrdersList* myOrders = new OrdersList();

    // Create some sample data for the other parameters
    vector<string> defenseList = {"territory1", "territory2"};
    vector<string> attackList = {"territory3", "territory4"};
    
    int reinforcementPool = 5;
    Territory t1("Canada", "America");
    Territory t2("USA", "America");

    vector<Territory> territories = {t1,t2};

    // Create a Player object using the constructor
    Player* p1 = new Player(myHand, *myTerritories, *myOrders, defenseList, attackList, reinforcementPool);

    Player* p2 = new Player(myHand, *myTerritories, *myOrders, defenseList, attackList, reinforcementPool);

    //add order in list of p1
    cout << "\nAdding Deploy order to player order list:" << endl;
    p1->GetOrdersList().addOrder(new Deploy(t1, p1, 5));
    
    p1->GetOrdersList().addOrder(new Advance(t1, t2, p1, 10));

    p1->GetOrdersList().addOrder(new Advance(t1, t2, p1, 10));

    p1->GetOrdersList().addOrder(new Bomb(t1, p1));

    p1->GetOrdersList().addOrder(new Blockade(t1, p1));

    p1->GetOrdersList().addOrder(new Airlift(t1, t2, p1, 2));

    p1->GetOrdersList().addOrder(new Negotiate(p1, p2));


    //validate and execute
    cout << "\nValidating and executing orders from list:" << endl;
    p1->GetOrdersList().executeOrders();

    return 0;
}