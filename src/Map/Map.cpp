#include "Map.h"

using namespace std;

ostream& operator <<(ostream& os, const Map& other) {
	throw exception("Not Implemented");
}
ostream& operator <<(ostream& os, const Territory& other) {
	throw exception("Not Implemented");
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

//vector<Territory> Map::GetConnections(Territory input)
//{
//    return vector<Territory>();
//}

/*
    True if matrix is a connected graph
    Finds next power of our adjacency matrix until it is entirely true or the next power equals the previous power
*/
bool Map::ValidateTerritories() {

    vector<vector<bool>> lastPower = CopyAdjacencyMatrix(this->adjacencyMatrix);

    bool matrixHasChanged = true;

    while (matrixHasChanged)
    {
        vector<vector<bool>> nextPower = AdjacencyMatrixMultiply(lastPower, this->adjacencyMatrix, this->territoryQuantity);

        if (MatrixIsTrue(nextPower))
            return true;

        matrixHasChanged = !CompareAdjacencyMatrices(lastPower, nextPower, this->territoryQuantity);

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
