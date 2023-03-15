#pragma once

#include "Player.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Territory
{
public:
	Territory(const string& territoryName, const string& continentName);
	Territory(const Territory& other);
	Territory();
	~Territory() = default;

	void Update(Player owner, int armyQuantity);
	string GetTerritoryName();
	string GetContinentName();
	static vector<Territory> GetTerritoriesOwnedBy(const Player& input, const vector<Territory>& inputList);

	friend ostream& operator<<(ostream& os, const Territory& territory){
		os << " " << *(territory.territoryName)
        << ", " << *(territory.continentName)
        << ", " << *(territory.owner)
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
	Map(string file);
	Map(int size, int continentAmount);
	Map(const Map& other);
	~Map() = default;

	vector<Territory> GetConnections(Territory& input);
	vector<Territory> GetConnections(int input);
	vector<Territory> GetTerritoriesOwnedBy(const Player& input);
	vector<Territory*> GetTerritories();
	bool Validate();
	bool ValidateSingleContinentProperty();
	bool ValidateTerritories();
	bool ValidateContinents();
	bool ValidateContinent(int continentIndex);

	friend ostream& operator<<(ostream& os, const Map& map){
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