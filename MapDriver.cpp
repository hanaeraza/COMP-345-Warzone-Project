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
    std::cout << map2.ValidateSingleContinentProperty();
    std::cout << map2.Validate();

    MapLoader maploader = MapLoader("cow.map");

    std::cout << "Printing CowMap\n";

    std::cout << maploader.GetMap();

    std::cout << "Cow Map Valid: " << maploader.GetMap().Validate();

    MapLoader invalidSubGraph = MapLoader("invalidSubGraph.map");

    std::cout << "Printing invalidSubGraph\n";

    std::cout << invalidSubGraph.GetMap();

    std::cout << "invalidSubGraph Valid: " << invalidSubGraph.GetMap().Validate();
}