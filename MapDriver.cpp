#include <iostream>
#include <vector>
#include "Map.h"
#include "Player.h"

// bool Validate();
// bool ValidateContinents();
// bool ValidateTerritories();
// bool ValidateSingleContinentProperty();

int bytesAllocated = 0;
int bytesDeallocated = 0;

void * operator new(size_t size)
{
  bytesAllocated += size;
  return malloc(size);
}

void operator delete(void * ptr, size_t size)
{
  bytesDeallocated += size;
  free(ptr);
}

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

  Player player = Player("Player1");
  Player player2 = Player("Player2");

  std::vector<Territory*> territories = map2.GetTerritories();

  for (size_t i = 0; i < territories.size(); i++)
  {
    if (i % 2 == 0)
      territories[i]->SetOwner(player);
    else
    territories[i]->SetOwner(player2);
  }

  std::vector<std::string> continents = map2.GetContinentsOwnedBy(player);

  for (size_t i = 0; i < territories.size(); i++)
  {
    std::cout << territories[i]->GetTerritoryName() << " Owned by " << territories[i]->GetOwner().playername << "\n";
  }
  
  
  MapLoader maploader = MapLoader("cow.map");

  std::cout << "Printing CowMap\n";

  std::cout << maploader.GetMap();

  std::cout << "Cow Map Valid: " << maploader.GetMap().Validate();

  MapLoader invalidSubGraph = MapLoader("invalidSubGraph.map");

  std::cout << "Printing invalidSubGraph\n";

  std::cout << invalidSubGraph.GetMap();

  std::cout << "invalidSubGraph Valid: " << invalidSubGraph.GetMap().Validate();
}