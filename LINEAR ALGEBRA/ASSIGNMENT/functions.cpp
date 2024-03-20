#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Function to get a diag_matrix
vector<vector<double>> diag_matrix(int size)
{
    vector<vector<double>> temp(size, vector<double>(size, 0));

    for (int i = 0; i < size; i++)
    {
        double value;
        cout << "Enter diagonal element of row " << i + 1 << ": ";
        cin >> value;
        temp[i][i] = value;
    }

    return temp;
}

// Function to check uppertriangle
bool is_triangular(vector<vector<double>> matrix, int n)
{
    int flag = 1;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (matrix[i][j] != 0)
            {
                flag = 0;
            }
        }
    }

    if (flag == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function to calculate LU decomposition
void LU(vector<vector<double>> &A, vector<vector<double>> &L, vector<vector<double>> &U)
{
    int n = A.size();

    L = vector<vector<double>>(n, vector<double>(n, 0.0));
    U = vector<vector<double>>(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++)
    {
        // U matrix is the same as the original matrix A
        for (int j = 0; j < n; j++)
        {
            U[i][j] = A[i][j];
        }
        // Diagonal elements of L are 1
        L[i][i] = 1.0;
        for (int k = i + 1; k < n; k++)
        {
            // Compute the multiplier for row k
            double multiplier = U[k][i] / U[i][i];
            L[k][i] = multiplier;
            for (int j = i; j < n; j++)
            {
                U[k][j] -= multiplier * U[i][j];
            }
        }
    }
}

// Function to calculate the dot product of two vectors
double dotProduct(const vector<double> &a, const vector<double> &b)
{
    double result = 0.0;
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        result += a[i] * b[i];
    }
    return result;
}

// Function to normalize a vector
void normalize(vector<double> &v)
{
    double length = sqrt(dotProduct(v, v));
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        v[i] /= length;
    }
}

// Function to perform QR decomposition
void qrDecomposition(vector<vector<double>> &A, vector<vector<double>> &Q, vector<vector<double>> &R)
{
    int n = A.size();
    int m = A[0].size();

    Q = vector<vector<double>>(n, vector<double>(m, 0.0));
    R = vector<vector<double>>(m, vector<double>(m, 0.0));

    vector<vector<double>> tempA = A;

    for (int j = 0; j < m; j++)
    {
        vector<double> column = {tempA[j].begin() + j, tempA[j].end()};

        for (int i = 0; i < j; i++)
        {
            vector<double> qj = Q[i];
            double dot = dotProduct(tempA[j], qj);
            for (int k = 0; k < n; k++)
            {
                column[k] -= dot * qj[k];
            }
        }

        normalize(column);

        for (int i = 0; i < n; i++)
        {
            Q[j][i] = column[i];
        }

        for (int i = j; i < m; i++)
        {
            R[j][i] = dotProduct(column, tempA[i]);
        }
    }
}
