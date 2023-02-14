#pragma once

#include "Map.h"
#include "Player.h"
#include "Player.cpp"

#include <random>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

ostream& operator <<(ostream &os, const Map &other) {
	for (int i = 0; i < *(other.territoryQuantity); i++)
    {
        os << "[ ";

        for (int j = 0; j < *(other.territoryQuantity); j++)
        {
            os << (*(other.adjacencyMatrix))[i][j] << " ";
        }
        
        os << "]" << (*(other.territories))[i] << "\n";
    }
    return os;
}

ostream& operator <<(ostream &os, MapLoader &other) {
    os << other.GetMap();
    return os;
}

ostream& operator <<(ostream &os, const vector<vector<bool>> &adjMatrix) {
	for (int i = 0; i < adjMatrix.size(); i++)
    {
        os << "[ ";

        for (int j = 0; j < adjMatrix.size(); j++)
        {
            os << adjMatrix[i][j] << " ";
        }
        
        os << "]" << "\n";
    }
    return os;
}

ostream& operator<<(ostream& os, const Territory& other) {
    os << " " << *(other.territoryName)
        << ", " << *(other.continentName)
        << ", " << *(other.owner)
        << ", " << *(other.armyQuantity);
    return os;
}

Territory::Territory(const string& territoryName, const string& continentName) :
		owner(new Player()), armyQuantity((new int(0)))	{
		this->territoryName = new string(territoryName);
		this->continentName = new string(continentName);
	}

Territory::Territory(const Territory& other) {
    this->territoryName = new string(*(other.territoryName));
    this->continentName = new string(*(other.continentName));
    this->owner = new Player(*(other.owner));
    this->armyQuantity = new int(*(other.armyQuantity));
}

Territory::Territory():
		territoryName(new string("NoTerritoryName")), continentName(new string("NoContinentName")),
		owner(nullptr), armyQuantity((new int(0))){
		
	}

Territory& Territory::operator =(const Territory &other) {
    if (this != &other)
    {
        delete territoryName;
        delete continentName;
        delete owner;
        delete armyQuantity;
        territoryName = new string(*(other.territoryName));
        continentName = new string(*(other.continentName));
        owner = new Player(*(other.owner));
        armyQuantity = new int(*(other.armyQuantity));
    }
    return *this;
}

bool Territory::operator==(const Territory& other) {
    return *territoryName == *other.territoryName &&
        *continentName == *other.continentName;
}


void Territory::Update(Player owner, int armyQuantity) {
    *(this->owner) = owner;
    *(this->armyQuantity) = armyQuantity;
}

string Territory::GetTerritoryName(){
    return *(this->territoryName);
}

string Territory::GetContinentName(){
    return *(this->continentName);
}

vector<Territory> Map::GetTerritories(){
    return *(this->territories);
}

void Map::GetBorders(string file){
    this->adjacencyMatrix = new vector<vector<bool>>(*(this->territoryQuantity),
    vector<bool>(*(this->territoryQuantity), false));

    ifstream inputMap(file);

    string lastLine;

    bool record = false;

    while (getline(inputMap, lastLine))
    {
        if (lastLine.find("[borders]") == 0)// Last line was [borders]
        {
            while (getline(inputMap, lastLine))
            {
                if (lastLine.empty() ||
                lastLine.find("[countries]") == 0 ||
                lastLine.find("[continents]") == 0 ||
                lastLine[0] == ';') {
                    break;
                }

                stringstream stream(lastLine);

                int num;

                vector<int> values;

                while (stream >> num)
                {
                    values.push_back(num - 1);
                    if (stream.peek() == ' ')
                        stream.ignore();
                }

                for (int i = 1; i < values.size(); i++)
                {
                    (*(this->adjacencyMatrix))[values[0]][values[i]] = true;
                    (*(this->adjacencyMatrix))[values[i]][values[0]] = true;
                }
            }
        }
    }
}

void Map::GetContinents(string file){
    this->continents = new vector<string>();

    ifstream inputMap(file);

    string lastLine;

    while (getline(inputMap, lastLine))
    {
        if (lastLine.find("[continents]") == 0)// Last line was [continents]
        {
            while (getline(inputMap, lastLine))
            {
                if (lastLine.empty() ||
                lastLine.find("[countries]") == 0 ||
                lastLine.find("[borders]") == 0 ||
                lastLine[0] == ';') {
                    break;
                }

                stringstream stream(lastLine);

                string cName, color;
                int cSize; 

                if ((stream >> cName >> cSize >> color)) {
                    (*(this->continents)).push_back(string(cName));
                }

                this->continentQuantity = new int((*(this->continents)).size());
            }
        }
    }
}

void Map::GetTerritories(string file){
    this->territories = new vector<Territory>();
    this->continentIndices = new vector<int>();

    ifstream inputMap(file);

    string lastLine;

    while (getline(inputMap, lastLine)){
        
        if (lastLine.find("[countries]") == 0)// Last line was [countries]
        {
            while (getline(inputMap, lastLine))
            {
                if (lastLine.empty() ||
                lastLine.find("[continents]") == 0 ||
                lastLine.find("[borders]") == 0 ||
                lastLine[0] == ';') {
                    this->territoryQuantity = new int((*(this->territories)).size());
                    break;
                }

                stringstream stream(lastLine);

                string tName;
                int tIndex, cIndex, a, b; 

                if ((stream >> tIndex >> tName >> cIndex >> a >> b)) {

                    (*(this->territories)).push_back(Territory(tName, (*(this->continents))[cIndex - 1]));
                    (*(this->continentIndices)).push_back(int(cIndex - 1));
                }
            }
        }
    }
}

Map::Map(string file){
    GetContinents(file);
    GetTerritories(file);
    GetBorders(file);
}

Map::Map(const Map& other){
    this->territoryQuantity = new int(*(other.territoryQuantity));
    this->territories = new vector<Territory>(*(other.territories));
    this->adjacencyMatrix = new vector<vector<bool>>(*(other.adjacencyMatrix));
    this->continentQuantity = new int(*(other.continentQuantity));
    this->continents = new vector<string>(*(other.continents));
    this->continentIndices = new vector<int>(*(other.continentIndices));
}

Map::Map(int size, int continentAmount) {
    this->territoryQuantity = new int(size);
    this->territories = new vector<Territory>(size);
    this->adjacencyMatrix = new vector<vector<bool>>(size, vector<bool>(size, false));
    this->continentQuantity = new int(continentAmount);
    this->continents = new vector<string>(continentAmount);
    this->continentIndices = new vector<int>(size);

    for (int i = 0; i < continentAmount; i++)
    {
        (*(this->continents))[i] = "Continent"+ to_string(i);
    }

    for (int i = 0; i < size; i++)
    {
        (*(this->continentIndices))[i] = ((double)continentAmount / (double)size) * i;
        (*(this->territories))[i] = Territory("Territory" + to_string(i),
            (*(this->continents))[(*(this->continentIndices))[i]]);
    }
    
    int countOuter = 0; //First index of current continent
    while (countOuter < size) //Create subgraphs for each continent
    {
        int countInner = 0; //Size of next continent graph
        int currentContinent = (*(this->continentIndices))[countOuter + countInner];
        int lastContinent = (*(this->continentIndices))[countOuter];

        while (currentContinent == lastContinent && countOuter + countInner < size)
        {
            countInner++;
            if (countOuter + countInner >= size)
                break;
            currentContinent = (*(this->continentIndices))[countOuter + countInner];
        }

        vector<vector<bool>> continentGraph = Map::RandomConnectedAdjacencyMatrix(countInner);

        for (size_t i = 0; i < countInner; i++)
        {
            for (size_t j = 0; j < countInner; j++)
            {
                int colContinentMatrix = i;
                int rowContinentMatrix = j;
                int colAdjMatrix = i + countOuter;
                int rowAdjMatrix = j + countOuter;

                (*(this->adjacencyMatrix))[rowAdjMatrix][colAdjMatrix] = 
                continentGraph[rowContinentMatrix][colContinentMatrix];

                (*(this->adjacencyMatrix))[colAdjMatrix][rowAdjMatrix] = 
                continentGraph[colContinentMatrix][rowContinentMatrix];
            }
        }
        countOuter += countInner;
    }

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, size - 1);

    while (!Map::AdjacencyMatrixIsConnected(*(this->adjacencyMatrix), size)) // Loop until connected
    {
        int row = distribution(generator);
        int col = distribution(generator);
        (*(this->adjacencyMatrix))[row][col] = (*(this->adjacencyMatrix))[col][row] = true;

        for (int i = 0; i < size; i++)
        {
            (*(this->adjacencyMatrix))[i][i] = false;
        }
    }
}

vector<Territory> Territory::GetTerritoriesOwnedBy(const Player &input, const vector<Territory> &inputList){
    vector<Territory> output = vector<Territory>();

    for (int i = 0; i < inputList.size(); i++)
    {
        if (*(inputList[i].owner) == input)
        {
            output.push_back(Territory(inputList[i]));
        }
    }

    return output;
}

vector<Territory> Map::GetTerritoriesOwnedBy(const Player &input){
    return Territory::GetTerritoriesOwnedBy(input, *territories);
}

vector<vector<bool>> Map::RandomConnectedAdjacencyMatrix(int size){
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, size - 1);

    vector<vector<bool>> adjacencyMatrix(size, vector<bool>(size, false));


    while (!Map::AdjacencyMatrixIsConnected(adjacencyMatrix, size)) // Loop until connected
    {
        int row = distribution(generator);
        int col = distribution(generator);
        adjacencyMatrix[row][col] = adjacencyMatrix[col][row] = true;

        for (int i = 0; i < size; i++)
        {
            adjacencyMatrix[i][i] = false;
        }
    }

    return adjacencyMatrix;
    
}

/*
    True if matrix is a connected graph
    Finds next power of our adjacency matrix until it is entirely true or the next power equals the previous power
*/

bool Map::AdjacencyMatrixIsConnected(vector<vector<bool>> input, int size){
    vector<vector<bool>> lastPower = CopyAdjacencyMatrix(input);

    vector<vector<vector<bool>>> history;

    history.push_back(lastPower);

    bool matrixHasChanged = true;

    while (matrixHasChanged)
    {
        vector<vector<bool>> nextPower = AdjacencyMatrixMultiply(lastPower, input, size);

        if (MatrixIsTrue(nextPower)) {
            return true;
        }

        for (size_t n = 0; n < history.size(); n++)
        {

            matrixHasChanged = !CompareAdjacencyMatrices(history[n], nextPower, size);

            if (!matrixHasChanged)
            {
                break;
            }
        }

        lastPower = nextPower;

        history.push_back(lastPower);
    }

    return false;
}

/*
    Returns a new square matrix using a simple version of matrix multiplication
*/
vector<vector<bool>> Map::AdjacencyMatrixMultiply(vector<vector<bool>> left, vector<vector<bool>> right, int size) {

    vector<vector<bool>> output(size, vector<bool>(size, 0));
    double sum;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            sum = false;
            for (int k = 0; k < size; k++)
            {
                sum = sum || (left[i][k] && right[k][j]);//sum += this.matrix[i, k] * A.matrix[k, j];
                if (sum)
                    break;
            }
            output[i][j] = left[i][j] || sum;
        }
    }
    return output;
}

/*
    Returns true when bool matrix is fully true and false otherwise
*/
bool Map::MatrixIsTrue(vector<vector<bool>> input) {

    int size = input.size();

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (!input[i][j])
                return false;
        }
    }
    return true;
}

vector<Territory> Map::GetConnections(Territory &input)
{
    for (size_t i = 0; i < *(this->territoryQuantity); i++)
    {
        if (input == (*this->territories)[i])
        {
            return GetConnections(i);
        }
    }

    return vector<Territory>();
}

vector<Territory> Map::GetConnections(int input)
{
    vector <Territory> output;

    for (size_t i = 0; i < *(this->territoryQuantity); i++)
    {
        if ((*this->adjacencyMatrix)[input][i])
        {
            output.push_back((*(this->territories))[input]);
        }
    }

    return output;
}

bool Map::Validate() {
    return Map::ValidateSingleContinentProperty() &&
    Map::ValidateTerritories() &&
    Map::ValidateContinents();
}

bool Map::ValidateSingleContinentProperty() {
    for (int i = 0; i < *(this->territoryQuantity); i++)
    {
        for (int j = i + 1; j < *(this->territoryQuantity); j++)
        {
            if ((*(this->territories))[i].GetTerritoryName() == (*(this->territories))[j].GetTerritoryName() &&
            (*(this->territories))[i].GetContinentName() == (*(this->territories))[j].GetContinentName())
            {
                return false;
            }
        }
    }
    return true;
}


bool Map::ValidateTerritories() {
    return AdjacencyMatrixIsConnected(*(this->adjacencyMatrix), *(this->territoryQuantity));
}

bool Map::ValidateContinents(){
    for (int i = 0; i < (*(this->continentQuantity)); i++)
    {
        if (!Map::ValidateContinent(i))
            return false;
    }
    return true;
}

bool Map::ValidateContinent(int continentIndex) {
    int tCount = 0;

    vector<int> territoryIndices = vector<int>();

    for (int i = 0; i < *(this->territoryQuantity); i++)
    {
        if (continentIndex == (*(this->continentIndices))[i]){
            tCount++;
            territoryIndices.push_back(i);
        }
    }
    
    vector<vector<bool>> adjacencyMatrix(tCount, vector<bool>(tCount, false));

    for (int i = 0; i < tCount; i++)
    {
        for (int j = 0; j < tCount; j++)
        {
            adjacencyMatrix[i][j] = (*(this->adjacencyMatrix))[territoryIndices[i]][territoryIndices[j]];
        }
    }


    return AdjacencyMatrixIsConnected(adjacencyMatrix, tCount);
}

/*
    Returns matrix with all entries copied
*/
vector<vector<bool>> Map::CopyAdjacencyMatrix(vector<vector<bool>> input) {

    int size = input.size();

    vector<vector<bool>> output(size, vector<bool>(size, 0));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            output[i][j] = input[i][j];
        }
    }
    return output;
}

/*
    Returns true when bool matrices contain the same values and false otherwise
*/
bool Map::CompareAdjacencyMatrices(vector<vector<bool>> left, vector<vector<bool>> right, int size) {

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (left[i][j] != right[i][j]) // Not Equal
                return false;
        }
    }
    return true;
}

void MapLoader::Load(string file){
    delete loadedMap;
    this->loadedMap = new Map(file);
}

MapLoader::MapLoader(){
    this->loadedMap = new Map(10,3);
}

MapLoader::MapLoader(string file){
    this->loadedMap = new Map(file);
}

MapLoader::MapLoader(const MapLoader& other){

}
