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
	Territory(const string& territoryName, const string& continentName) :
		owner(nullptr), armyQuantity((new int(0)))	{
		this->territoryName = new string(territoryName);
		this->continentName = new string(continentName);
	}
	Territory(const Territory& other);
	Territory():
		territoryName(new string("NoTerritoryName")), continentName(new string("NoContinentName")),
		owner(nullptr), armyQuantity((new int(0))){
		
	}
	~Territory() = default;

	void Update(Player owner, int armyQuantity);
	static vector<Territory> GetTerritoriesOwnedBy(const Player& input, const vector<Territory>& inputList);

	friend ostream& operator<<(ostream& os, const Territory& territory);
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
	~Map() = default;

	vector<Territory> GetConnections(Territory& input);
	vector<Territory> GetConnections(int input);
	vector<Territory> GetTerritoriesOwnedBy(const Player& input);
	bool ValidateTerritories();
	bool ValidateContinents();
	bool ValidateContinent(int continentIndex);

	friend ostream& operator<<(ostream& os, const Map& territory);
	Map& operator =(Map &other);
	bool operator ==(Map &other);
private:
	int* territoryQuantity;
	vector<Territory>* territories;
	vector<vector<bool>>* adjacencyMatrix; // https://en.wikipedia.org/wiki/Adjacency_matrix
	int* continentQuantity;
	vector<string>* continents;
	vector<int>* continentIndices; // Shows continent index of every territory

	vector<vector<bool>> BuildContinentAdjacencyMatrix(int continentIndex);
	void GetTerritories(string file);
	void GetContinents(string file);
	void GetBorders(string file);

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
	~MapLoader();

	MapLoader& operator =(const MapLoader& other);
	bool& operator ==(const MapLoader& other);
private:
	Map* loadedMap;
};