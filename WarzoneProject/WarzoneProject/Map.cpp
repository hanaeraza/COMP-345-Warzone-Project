#include "Map.h"

using namespace std;

ostream& operator <<(ostream &os, const Map &other) {
	throw exception("Not Implemented");
}

ostream& operator<<(ostream& os, const Territory& other) {
    os << "TerritoryName: " << *(other.territoryName)
        << "\nContinentName: " << *(other.continentName)
        << "\nOwner: " << *(other.owner)
        << "\nArmy Amount: " << *(other.armyQuantity);
    return os;
}

Territory::Territory(const Territory& other) {
    this->territoryName = new string(*(other.territoryName));
    this->continentName = new string(*(other.continentName));
    this->owner = new Player(*(other.owner));
    this->armyQuantity = new int(*(other.armyQuantity));
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
            output[i][j] = sum;
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

    throw exception("Invalid Territory");
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

/*
    True if matrix is a connected graph
    Finds next power of our adjacency matrix until it is entirely true or the next power equals the previous power
*/
bool Map::ValidateTerritories() {

    vector<vector<bool>> lastPower = CopyAdjacencyMatrix(*(this->adjacencyMatrix));

    bool matrixHasChanged = true;

    while (matrixHasChanged)
    {
        vector<vector<bool>> nextPower = AdjacencyMatrixMultiply(lastPower, *(this->adjacencyMatrix), *(this->territoryQuantity));

        if (MatrixIsTrue(nextPower))
            return true;

        matrixHasChanged = !CompareAdjacencyMatrices(lastPower, nextPower, *(this->territoryQuantity));

        lastPower = nextPower;
    }

    return false;
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
