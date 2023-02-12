#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


class Card {

private:
    
public:
    string type;
    Card(std::string v) : type(v) {}

    ~Card();

    Card& operator=(const Card& other);
    //Card* play(Hand* hand, Deck* deck);
    void play();
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
    int size = 0;
    const int maxSize = 5;
    Card** cards;

public:
    Hand();
    Hand(const Hand& h);
    ~Hand();

    void addCard(Card* c);
    void printHand();
    // Hand::Hand& operator=(const Hand& h);
};

