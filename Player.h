#pragma once

#include <iostream>
#include <ostream>

using namespace std;

class Player
{
public:
	friend ostream& operator <<(ostream& os, const Player& other);

	bool operator ==(const Player &other);
};