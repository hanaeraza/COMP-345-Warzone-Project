#include <iostream>
#include "Card.h"
#include "orders.cpp"
using namespace std;

//Copy Constructor
//Card::Card(const Card& c) {
//	this->type = c.type;
//}
//Destructor
Card::~Card() {

}
//Play Method

//Constructor
Hand::Hand() {
	cards = new Card * [maxSize];
}
//Copy Constructor
//Hand::Hand(const Hand& h) {
//	this->size = h.size;
//	this->cards = new Card * [maxSize];
//	for (int i = 0; i < size; i++) {
//		this->cards[i] = new Card(*h.cards[i]);
//	}
//}
//Destructor
Hand::~Hand() {
	for (int i = 0; i < size; i++) {
		delete cards[i];
	}
	delete[] cards;
}
// Method to print cards in Hand
void Hand::printHand() {
	 for (int i = 0; i < maxSize; i++) {
        if (cards[i] != nullptr) {
            cout << cards[i]->type << " ";
        }
        else {
            cout << "";
        }
    }
    cout << endl;
}
//Method to add a card to a hand
void Hand::addCard(Card* c) {
	if (size < maxSize) {
		cards[size] = c;
		size++;
	}
	else {
		std::cout << "Hand is already full." << std::endl;
	}
}



//Constructor Generates Deck
Deck::Deck() {
	cards = new Card * [size];

	for (int i = 0; i < 10; i++) {
		cards[i] = new Card("Bomb");
		cards[i + 10] = new Card("Reinforcement");
		cards[i + 20] = new Card("Blockade");
		cards[i + 30] = new Card("Airlift");
		cards[i + 40] = new Card("Diplomacy");
	}
}
//Copy Constructor
//Deck::Deck(const Deck& d) {
//	this->size = d.size;
//	this->cards = new Card * [size];
//	for (int i = 0; i < size; i++) {
//		this->cards[i] = new Card(*d.cards[i]);
//	}
//}
//Destructor
Deck::~Deck() {
	for (int i = 0; i < size; i++) {
		delete cards[i];
	}
	delete[] cards;
}
//Randomly Draw Card from Deck into Hand
Card* Deck::draw() {

	srand(time(NULL));
	int index = rand() % size;
	Card* drawnCard = cards[index];
	for (int i = index; i < size - 1; i++) {
		cards[i] = cards[i + 1];
	}
	size--;
	return drawnCard;
}
void Card::play(Hand* hand, Deck *deck) {
	newOrder orderCreate;  //
    OrdersList order_list; //creates an order list

	order_list.addOrder(orderCreate.createOrder(this->type)); 
    if (hand && deck) {
        // Remove the card from the hand.
        for (int i = 0; i < hand->size; i++) {
            if (hand->cards[i] == this) {
                hand->cards[i] = nullptr;
                hand->size--;
                break;
            }
        }

        // Return the card to the deck.
        deck->cards[deck->size] = this;
        deck->size++;
    }
}
