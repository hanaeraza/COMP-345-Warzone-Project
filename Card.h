#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Player.cpp"
using namespace std;

class Card;
class Deck;
class Hand;

class Card {

private:

public:
    string type;
    
    Card(std::string v) : type(v) {}

    ~Card();

    
    void play(Hand* hand, Deck* deck);
    // bool removeFromHand(Hand* hand, Deck* deck);

};

class Deck {
private:

public:
    int size = 50;
    Card** cards;
    Deck();
    Deck(const Deck& d);
    ~Deck();
    Card* draw();
    //Card* operator[](int index) const { return deck[index]; }
};

class Hand {
private:


public:

    int size = 0;
    const int maxSize = 5;
    Card** cards;

    Hand();
    Hand(const Hand& h);
    ~Hand();

    void addCard(Card* c);
    void printHand();

    // Hand::Hand& operator=(const Hand& h);
};

