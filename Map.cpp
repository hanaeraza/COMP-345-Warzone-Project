#pragma once

#include "Map.h"
#include "Player.h"

#include <random>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// /*
//     Overriding <<
//     Inserts readable sequence into output stream
// */
// ostream& operator <<(ostream &os, const Map &other) {
// 	for (int i = 0; i < *(other.territoryQuantity); i++)
//     {
//         os << "[ ";

//         for (int j = 0; j < *(other.territoryQuantity); j++)
//         {
//             os << (*(other.adjacencyMatrix))[i][j] << " ";
//         }
        
//         os << "]" << (*(other.territories))[i] << "\n";
//     }
//     return os;
// }

// /*
//     Overriding <<
//     Inserts readable sequence into output stream
// */
// ostream& operator <<(ostream &os, MapLoader &other) {
//     os << other.GetMap();
//     return os;
// }

/*
    Overriding <<
    Inserts readable sequence into output stream
*/
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

// /*
//     Overriding <<
//     Inserts readable sequence into output stream
// */
// ostream& operator<<(ostream& os, const Territory& other) {
//     os << " " << *(other.territoryName)
//         << ", " << *(other.continentName)
//         << ", " << *(other.owner)
//         << ", " << *(other.armyQuantity);
//     return os;
// }

/*
    Parametrized Territory Constructor which assigns territoryName and continentName
*/
Territory::Territory(const string& territoryName, const string& continentName) :
		owner(new Player()), armyQuantity((new int(0)))	{
		this->territoryName = new string(territoryName);
		this->continentName = new string(continentName);
	}

/*
    Territory Copy Constructor
*/
Territory::Territory(const Territory& other) {
    this->territoryName = new string(*(other.territoryName));
    this->continentName = new string(*(other.continentName));
    this->owner = new Player(*(other.owner));
    this->armyQuantity = new int(*(other.armyQuantity));
}

/*
    Default Territory Constructor
*/
Territory::Territory():
		territoryName(new string("NoTerritoryName")), continentName(new string("NoContinentName")),
		owner(new Player()), armyQuantity((new int(0))){
		
	}

/*
    Overriding =
    Deletes hanging values to prevent memory leak then copies from other Territory
*/
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

/*
    Overriding =
    Deletes hanging values to prevent memory leak then copies from other Map
*/
Map& Map::operator =(const Map &other) {
    if (this != &other)
    {
        delete territoryQuantity;
        delete territories;
        delete adjacencyMatrix;
        delete continentQuantity;
        delete continents;
        delete continentIndices;

        this->territoryQuantity = new int(*(other.territoryQuantity));
        this->territories = new vector<Territory*>(*(other.territories));
        this->adjacencyMatrix = new vector<vector<bool>>(*(other.adjacencyMatrix));
        this->continentQuantity = new int(*(other.continentQuantity));
        this->continents = new vector<string>(*(other.continents));
        this->continentIndices = new vector<int>(*(other.continentIndices));
    }
    return *this;
}

/*
    Overriding ==
    Returns true if this == other
*/
bool Territory::operator==(const Territory& other) {
    return *territoryName == *other.territoryName &&
        *continentName == *other.continentName;
}

/*
    Returns territoryName
*/
void Territory::Update(Player owner, int armyQuantity) {
    *(this->owner) = owner;
    *(this->armyQuantity) = armyQuantity;
}

/*
    Returns territoryName
*/
string Territory::GetTerritoryName(){
    return *(this->territoryName);
}

/*
    Returns continentName
*/
string Territory::GetContinentName(){
    return *(this->continentName);
}

Player Territory::GetOwner(){
    return *(this->owner);
}

/*
    Returns territories
*/
vector<Territory*> Map::GetTerritories(){
    return *(this->territories);
}

/*
    Creates Adjacency Matrix by reading file.
    Ex file: europe.map
*/
void Map::CreateBorders(string file){
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

/*
    Creates Continents by reading file.
    Ex file: europe.map
*/
void Map::CreateContinents(string file){
    this->continents = new vector<string>();
    this->continentBonus = new vector<int>();

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
                int cBonus; 

                if ((stream >> cName >> cBonus >> color)) {
                    (*(this->continents)).push_back(string(cName));
                    (*(this->continentBonus)).push_back(cBonus);
                }

                this->continentQuantity = new int((*(this->continents)).size());
            }
        }
    }
}

/*
    Creates Territories by reading file.
    Ex file: europe.map
*/
void Map::CreateTerritories(string file){
    this->territories = new vector<Territory*>();
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

                    (*(this->territories)).push_back(new Territory(tName, (*(this->continents))[cIndex - 1]));
                    (*(this->continentIndices)).push_back(int(cIndex - 1));
                }
            }
        }
    }
}

/*
    Creates Map by reading file.
    Ex file: europe.map
*/
Map::Map(string file){
    CreateContinents(file);
    CreateTerritories(file);
    CreateBorders(file);
}

/*
    Map Copy
*/
Map::Map(const Map& other){
    this->territoryQuantity = new int(*(other.territoryQuantity));
    this->territories = new vector<Territory*>((*(other.territories)).begin(), (*(other.territories)).end());
    this->adjacencyMatrix = new vector<vector<bool>>(*(other.adjacencyMatrix));
    this->continentQuantity = new int(*(other.continentQuantity));
    this->continents = new vector<string>(*(other.continents));
    this->continentIndices = new vector<int>(*(other.continentIndices));
    this->continentBonus = new vector<int>(*(other.continentBonus));
}

Map::Map(){
    this->territoryQuantity = new int(0);
    this->territories = new vector<Territory*>();
    this->adjacencyMatrix = new vector<vector<bool>>();
    this->continentQuantity = new int(0);
    this->continents = new vector<string>();
    this->continentIndices = new vector<int>();
    this->continentBonus = new vector<int>();
}

/*
    Returns new generated map of size size and with continentAmount continents
*/
Map::Map(int size, int continentAmount) {
    this->territoryQuantity = new int(size);
    this->territories = new vector<Territory*>(size);
    this->adjacencyMatrix = new vector<vector<bool>>(size, vector<bool>(size, false));
    this->continentQuantity = new int(continentAmount);
    this->continents = new vector<string>(continentAmount);
    this->continentIndices = new vector<int>(size);
    this->continentBonus = new vector<int>(continentAmount);

    for (int i = 0; i < continentAmount; i++)
    {
        (*(this->continents))[i] = "Continent"+ to_string(i);
    }

    for (int i = 0; i < size; i++)
    {
        (*(this->continentIndices))[i] = ((double)continentAmount / (double)size) * i;
        (*(this->territories))[i] = new Territory("Territory" + to_string(i),
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

    for (int i = 0; i < continentBonus->size(); i++)
    {
        (*continentBonus)[i] = distribution(generator) + 1;
    }

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

/*
    Returns territories owned by player given list of territories
*/
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

/*
    Returns Continents owned by player
*/
vector<string> Map::GetContinentsOwnedBy(const Player& input){
    vector<string> output = vector<string>();
    vector<bool> hasContinent(continents->size(), false);
    for (int i = 0; i < continentIndices->size(); i++)
    {
        if ((*territories)[(*continentIndices)[i]]->GetOwner() == input)
        {
            hasContinent[i] = false;
        }
    }
    for (int i = 0; i < hasContinent.size(); i++)
    {
        output.push_back((*continents)[i]);
    }
    
    return output;
}

/*
    Returns territories owned by player
*/
vector<Territory> Map::GetTerritoriesOwnedBy(const Player &input){
    vector<Territory> tVector = vector<Territory>();
    for (const auto& t : *territories) {
        tVector.push_back(*t);
    }
    
    return Territory::GetTerritoriesOwnedBy(input, tVector);
}

int Map::GetContinentBonus(string continentInput){
    for (int i = 0; i < continents->size(); i++)
    {
        if ((*continents)[i] == continentInput)
        {
            return (*continentBonus)[i];
        }
    }
    return -1;
}

/*
    Creates Adjacency Matrix and adds connections until it is fully connected
*/
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

/*
    Returns connected territories to territory at node
*/
vector<Territory> Map::GetConnections(Territory &input)
{
    for (size_t i = 0; i < *(this->territoryQuantity); i++)
    {
        if (input == *(*this->territories)[i])
        {
            return GetConnections(i);
        }
    }

    return vector<Territory>();
}

/*
    Returns connected territories to territory at node at index
*/
vector<Territory> Map::GetConnections(int input)
{
    vector <Territory> output;

    for (size_t i = 0; i < *(this->territoryQuantity); i++)
    {
        if ((*this->adjacencyMatrix)[input][i])
        {
            output.push_back(*(*(this->territories))[input]);
        }
    }

    return output;
}

/*
    Returns true map is valid and false otherwise
*/
bool Map::Validate() {
    return Map::ValidateSingleContinentProperty() &&
    Map::ValidateTerritories() &&
    Map::ValidateContinents();
}

/*
    Returns true if every territory name is associated with a single continent and false otherwise
*/
bool Map::ValidateSingleContinentProperty() {
    for (int i = 0; i < *(this->territoryQuantity); i++)
    {
        for (int j = i + 1; j < *(this->territoryQuantity); j++)
        {
            if ((*(*(this->territories))[i]).GetTerritoryName() == (*(*(this->territories))[j]).GetTerritoryName() &&
            (*(*(this->territories))[i]).GetContinentName() == (*(*(this->territories))[j]).GetContinentName())
            {
                return false;
            }
        }
    }
    return true;
}

/*
    Returns true if map is a connected graph and false otherwise
*/
bool Map::ValidateTerritories() {
    return AdjacencyMatrixIsConnected(*(this->adjacencyMatrix), *(this->territoryQuantity));
}

/*
    Returns true if all continents are connected graphs and false otherwise
*/
bool Map::ValidateContinents(){
    for (int i = 0; i < (*(this->continentQuantity)); i++)
    {
        if (!Map::ValidateContinent(i))
            return false;
    }
    return true;
}

/*
    Returns true if continent is connected graphs and false otherwise
*/
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

/*
    Loads a map from file path.
    Ex: europe.map
*/
void MapLoader::Load(string file){
    delete loadedMap;
    this->loadedMap = new Map(file);
}

/*
    Creates a MapLoader and generates random map
*/
MapLoader::MapLoader(int size, int continentAmount){
    this->loadedMap = new Map(size,continentAmount);
}

/*
    Creates a MapLoader and generates map from file
*/
MapLoader::MapLoader(string file){
    this->loadedMap = new Map(file);
}

/*
    Creates an empty MapLoader
*/
MapLoader::MapLoader(){
    this->loadedMap = new Map();
}

/*
    MapLoader Copy Constructor
*/
MapLoader::MapLoader(const MapLoader& other){
    this->loadedMap = new Map(*(other.loadedMap));
}

/*
    Returns current map object
*/
Map MapLoader::GetMap(){
    return *(this->loadedMap);
}

/*
    Assignment Operator:
    Deletes current data members then copies from other
*/
MapLoader& MapLoader::operator =(const MapLoader& other){
    if (this != &other)
    {
        delete loadedMap;

        this->loadedMap = new Map(*(other.loadedMap));
    }
    return *this;
}