#include <iostream>
#include "Map.h"
#include "Map.cpp"

int main()
{
    Map map = Map(10, 3);

    std::cout << "Printing Map\n";

    std::cout << map;

    Map map2 = Map("europe.map");

    std::cout << "Printing Map2\n";

    std::cout << map2;

    std::cout << "Printed Map2\n";

    std::cout << map2.ValidateContinents();
    std::cout << map2.ValidateTerritories();
}