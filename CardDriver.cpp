#include "GameEngine.h"

#include <string>
#include <iostream>
using namespace std;
int main() {
	
	GameEngine GameEngine;

    // Run until end state is reached
    while(GameEngine.getCurrentState() != "EndState") {
    GameEngine.update(); 
    }
	return 0;
}
