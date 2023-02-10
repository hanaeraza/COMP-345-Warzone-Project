#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class MapLoader
{
public:
	MapLoader();
	~MapLoader();
private:
	Map* loadedMap;
};

class Map
{
public:
	Map(string file);
	~Map();

	vector<Territory> GetConnections(Territory& input);
	bool ValidateTerritories();

	Map& operator =(Map& other);
private:
	int territoryQuantity;
	vector<Territory> territories;
	vector<vector<bool>> adjacencyMatrix;

	static vector<vector<bool>> AdjacencyMatrixMultiply(vector<vector<bool>> left, vector<vector<bool>> right, int size);
	static bool MatrixIsTrue(vector<vector<bool>> input);
	static vector<vector<bool>> CopyAdjacencyMatrix(vector<vector<bool>> input);
	static bool CompareAdjacencyMatrices(vector<vector<bool>> left, vector<vector<bool>> right, int size);
};

class Territory
{
public:
	Territory(string territoryName, string continentName);
	~Territory();

	Territory& operator =(Territory& other);
private:
	string territoryName;
	string continentName;
};
