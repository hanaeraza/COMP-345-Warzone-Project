#include <iostream>
#include "Card.h"
using namespace std;

//Card::Card(string *cType) {
	//this->type = cType;
//}
//Card::Card(const Card& c) {
//	this->type = c.type;
//}
Card::~Card() {
	
}

//assignment operator 
//Card::Card& operator=(const Card& c)
//{
//	this->type = c.type;
//	return *this;
//}

void Card::play() {
	cout << "Playing card of type: " << type << endl;
}

Hand::Hand() {
	cards = new Card * [maxSize];
}
Hand::Hand(const Hand& h) {
	
}
Hand::~Hand() {
	for (int i = 0; i < size; i++) {
		delete cards[i];
	}
	delete[] cards;
}
void Hand::printHand() {
	std::cout << "Cards in hand: ";
	for (int i = 0; i < size; i++) {
		std::cout << cards[i]->type << " ";
	}
	std::cout << std::endl;
}
void Hand::addCard(Card* c) {
	if (size < maxSize) {
		cards[size] = c;
		size++;
	}
	else {
		std::cout << "Hand is already full." << std::endl;
	}
}
//assignment operator
//Hand::Hand& operator=(const Hand& h)
//{
//	this->numCards = h.numCards;
//	return *this;
//}

Deck::Deck() {
	// write code to randomly generate deck
	cards = new Card * [size];

	for (int i = 0; i < 10; i++) {
		cards[i] = new Card("Bomb");
		cards[i + 10] = new Card("Reinforcement");
		cards[i + 20] = new Card("Blockade");
		cards[i + 30] = new Card("Airlift");
		cards[i + 40] = new Card("Diplomacy");
	}
}

Deck::Deck(const Deck& d) {
	//write code to copy this->deck into d
}
Deck::~Deck() {
	for (int i = 0; i < size; i++) {
		delete cards[i];
	}
	delete[] cards;
}
  Card *Deck::draw() {

	srand(time(NULL));
	int index = rand() % size;
	Card* drawnCard = cards[index];
	for (int i = index; i < size - 1; i++) {
		cards[i] = cards[i + 1];
	}
	size--;
	return drawnCard;
}
int main() {
	Deck* deck = new Deck();
	Hand* hand = new Hand();

	for (int i = 0; i < 5; i++) {
		hand->addCard(deck->draw());
	}
	hand->printHand();
	return 0;
}