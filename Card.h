#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;



class Player;
class Card;
class Deck;
class Hand;

class Card {

private:

public:
    string type;
    
    Card(std::string v) : type(v) {};
    Card(const Card& c);
    ~Card();

    Card& operator=(const Card& c);
    
    void play(Hand* hand, Deck* deck, Player *player);
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
    Deck& operator=(const Deck& d);
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
    Hand& operator=(const Hand& h);
};
