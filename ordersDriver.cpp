#include "orders.h"
#include "player.h"
#include "card.h"
#include "map.h"
using namespace std;

class Player;
class Territory;

int main() {
    
    int reinforcementPool = 5;
    Territory t1("Canada", "America");
    Territory t2("USA", "America");
    Territory t3("Mexico", "America");
    
    // Create a Player object using the constructor
    Player* p1 = new Player();
    Player* p2 = new Player();


    t1.SetOwner(*p1);
    t2.SetOwner(*p1);
    t3.SetOwner(*p2);

    t1.SetArmyQuantity(50);
    t2.SetArmyQuantity(50);
    t3.SetArmyQuantity(50);

    //add order in list of p1
    cout << "\nAdding orders to p1 order list:" << endl;
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