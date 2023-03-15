#include <chrono>
#include <iostream>
#include <omp.h>
using namespace std;

int **sequential_multiply(int **a, int **b, int n1, int m1, int m2)
{
    int **c = new int *[n1];

    for (int i = 0; i < n1; i++)
    {
        c[i] = new int[m2];
        for (int j = 0; j < m2; j++)
        {
            c[i][j] = 0;
        }
    }
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            for (int k = 0; k < m1; k++)
            {
                c[i][j] += (a[i][k] * b[k][j]);
            }
        }
    }
    auto end = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "time sequential multiply : " << time.count() << " ms\n";
    return c;
}

int **sequential_multiply_boost(int **a, int **b, int n1, int m1, int m2)
{
    int **c = new int *[n1];

    for (int i = 0; i < n1; i++)
    {
        c[i] = new int[m2];
        for (int j = 0; j < m2; j++)
        {
            c[i][j] = 0;
        }
    }
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < n1; i++)
    {
        for (int k = 0; k < m1; k++)
        {
            for (int j = 0; j < m2; j++)
            {
                c[i][j] += (a[i][k] * b[k][j]);
            }
        }
    }
    auto end = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "time sequential multiply (boost): " << time.count() << " ms\n";
    return c;
}

int **parallel_multiply(int **a, int **b, int n1, int m1, int m2)
{
    int **c = new int *[n1];

    for (int i = 0; i < n1; i++)
    {
        c[i] = new int[m2];
        for (int j = 0; j < m2; j++)
        {
            c[i][j] = 0;
        }
    }
    int threadsNum = omp_get_num_procs();
    omp_set_num_threads(threadsNum);
    int i, j, k;
    auto start = chrono::steady_clock::now();
#pragma omp parallel for shared(a, b, c) private(i, j, k)
    for (i = 0; i < n1; i++)
    {
        for (k = 0; k < m1; k++)
        {
            for (j = 0; j < m2; j++)
            {
                c[i][j] += (a[i][k] * b[k][j]);
            }
        }
    }
    auto end = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "time parallel multiply: " << time.count() << " ms\n";
    return c;
}

void create_matrix(int **arr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = new int[m];
        for (int j = 0; j < m; j++)
        {
            arr[i][j] = rand() % 100 + 1;
        }
    }
    return;
}

int main()
{
    srand(time(NULL));
    int n1 = 1000;
    int m1 = 1000;
    int **A = new int *[n1];
    create_matrix(A, n1, m1);

    int n2 = 1000;
    int m2 = 1000;
    int **B = new int *[n2];
    create_matrix(B, n2, m2);

    int **C;
    C = sequential_multiply(A, B, n1, m1, m2);
    C = sequential_multiply_boost(A, B, n1, m1, m2);
    C = parallel_multiply(A, B, n1, m1, m2);
}

// g++ lab3.cpp -o lab3 -fopenmp -O3