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
		owner(nullptr), armyQuantity(0)	{
		this->territoryName = new string(territoryName);
		this->continentName = new string(continentName);
	}
	~Territory() = default;

	void Update(Player owner, int armyQuantity);

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
	~Map();

	vector<Territory> GetConnections(Territory& input);
	vector<Territory> GetConnections(int input);
	bool ValidateTerritories();

	Map& operator =(Map &other);
	bool operator ==(Map &other);
private:
	int* territoryQuantity;
	vector<Territory>* territories;
	vector<vector<bool>>* adjacencyMatrix;

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

	MapLoader& operator =(MapLoader& other);
	MapLoader& operator ==(MapLoader& other);
private:
	Map* loadedMap;
};