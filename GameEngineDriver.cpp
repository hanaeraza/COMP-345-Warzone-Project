#include <iostream>
#include <string>
#include "GameEngine.h"
#include "GameEngine.cpp"
using namespace std;

   int main() {
    GameEngine GameEngine;

    // Run until end state is reached
    while(GameEngine.getCurrentState() != "EndState") {
    GameEngine.update(); 
    }

    return 0;
}