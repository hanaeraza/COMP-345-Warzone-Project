#include "Card.cpp"

#include <iostream>
using namespace std;
int main() {
	Deck* deck = new Deck();
	Hand* hand = new Hand();
	//Player* Player = new Player();
	for (int i = 0; i < 5; i++) {
		hand->addCard(deck->draw());
	}
	cout << "Cards in Hand: " << endl;
	
	hand->printHand();
	int count = 0;
	cout << "Remaining cards in deck: ";
	for (int i = 0; i < deck->size; i++) {
		cout << deck->cards[i]->type << " ";
		count++;
	}
	cout << count << " cards left in the Deck" << endl;
	count = 0;
	hand->cards[2]->play(hand,deck);
	cout << "Cards in Hand: " << endl;
	hand->printHand();

	cout << "Remaining cards in deck: ";
	for (int i = 0; i < deck->size; i++) {
		cout << deck->cards[i]->type << " ";
		count++;
	}
	cout << count << " cards left in the deck" << endl;
	//Player* player = new Player(hand);

	return 0;
}