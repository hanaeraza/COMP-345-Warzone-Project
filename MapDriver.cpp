#include <iostream>
#include "Map.h"
#include "Map.cpp"

int main()
{
    Map map = Map(10, 3);

    std::cout << "Printing Map\n";

    std::cout << map;
}