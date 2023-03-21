#pragma once

#include "Player.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Player;

class Territory
{
public:
	Territory(const string& territoryName, const string& continentName);
	Territory(const Territory& other);
	Territory();
	~Territory() = default;

	void Update(Player owner, int armyQuantity);
	void Update(Player owner);
	void SetOwner(const Player owner);
	string GetTerritoryName();
	string GetContinentName();
	int GetArmyQuantity();
	void SetArmyQuantity(int input);
	Player GetOwner();
	static vector<Territory> GetTerritoriesOwnedBy(const Player& input, const vector<Territory>& inputList);

	friend ostream& operator<<(ostream& os, const Territory& territory){
		os << " " << *(territory.territoryName)
        << ", " << *(territory.continentName)
        << ", " << *(territory.armyQuantity);
    return os;
	}
	Territory& operator =(const Territory& other);
	bool operator ==(const Territory& other);
private:
	string* territoryName;
	string* continentName;
	Player* owner;
	int* armyQuantity;
};

class Map
{
public:
	Map();
	Map(string file);
	Map(int size, int continentAmount);
	Map(const Map& other);
	~Map() = default;

	vector<Territory> GetConnections(Territory& input);
	vector<Territory> GetConnections(int input);
	vector<Territory> GetTerritoriesOwnedBy(const Player& input);
	vector<string> GetContinentsOwnedBy(const Player& input);
	vector<Territory*> GetTerritories();
	int GetContinentBonus(string continentInput);
	bool Validate();
	bool ValidateSingleContinentProperty();
	bool ValidateTerritories();
	bool ValidateContinents();
	bool ValidateContinent(int continentIndex);

	friend ostream& operator<<(ostream& os, const Map& map){
		for (int i = 0; i < map.continents->size(); i++)
		{
			os << (*(map.continents))[i] << " Bonus: " << (*(map.continentBonus))[i] << "\n";
			for (int j = 0; j < map.continentIndices->size(); j++)
			{
				if ((*(map.continentIndices))[j] == i)
				{
					os << *((*(map.territories))[j]) << "\n";
				}
				
			}
			
		}
		
		for (int i = 0; i < *(map.territoryQuantity); i++)
			{
				os << "[ ";

				for (int j = 0; j < *(map.territoryQuantity); j++)
				{
						os << (*(map.adjacencyMatrix))[i][j] << " ";
				}
				
				os << "]" << *((*(map.territories))[i]) << "\n";
			}
			return os;
	}
	Map& operator =(const Map &other);
private:
	int* territoryQuantity;
	vector<Territory*>* territories;
	vector<vector<bool>>* adjacencyMatrix; // https://en.wikipedia.org/wiki/Adjacency_matrix
	int* continentQuantity;
	vector<string>* continents;
	vector<int>* continentBonus;	// Number associated with continent at index
	vector<int>* continentIndices; // Shows continent index of every territory

	vector<vector<bool>> BuildContinentAdjacencyMatrix(int continentIndex);
	void CreateTerritories(string file);
	void CreateContinents(string file);
	void CreateBorders(string file);

	static vector<vector<bool>> RandomConnectedAdjacencyMatrix(int size);
	static bool AdjacencyMatrixIsConnected(vector<vector<bool>> input, int size);
	static vector<vector<bool>> AdjacencyMatrixMultiply(vector<vector<bool>> left, vector<vector<bool>> right, int size);
	static bool MatrixIsTrue(vector<vector<bool>> input);
	static vector<vector<bool>> CopyAdjacencyMatrix(vector<vector<bool>> input);
	static bool CompareAdjacencyMatrices(vector<vector<bool>> left, vector<vector<bool>> right, int size);
};

class MapLoader
{
public:
	MapLoader();
	MapLoader(int size, int continentAmount);
	MapLoader(string file);
	MapLoader(const MapLoader& other);
	~MapLoader() = default;

	Map GetMap();
	void Load(string file);
	friend ostream& operator<<(ostream& os, MapLoader& map){
		os << map.GetMap();
    return os;
	}
	MapLoader& operator =(const MapLoader& other);

private:
	Map* loadedMap;
};