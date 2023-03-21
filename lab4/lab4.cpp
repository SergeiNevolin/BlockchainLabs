#include <iostream>
#include <chrono>
#include <omp.h>

using namespace std;

void randomize_matrix(double **arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            arr[i][j] = rand() % 100 + 1;
        }
    }
    return;
}

void randomize_array(double *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
    return;
}

int main()
{
    int n = 4000;

    double **matr = new double *[n];
    double *B = new double[n];
    double *x = new double[n];

    randomize_matrix(matr, n);
    randomize_array(B, n);

    int threadsNum = omp_get_num_procs();
    omp_set_num_threads(threadsNum);

    auto start = chrono::steady_clock::now();

    #pragma omp parallel for
    for (int k = 0; k < n; k++)
    {
        for (int j = k + 1; j < n; j++)
        {
            double d = matr[j][k] / matr[k][k];
            for (int i = k; i < n; i++)
            {
                matr[j][i] = matr[j][i] - d * matr[k][i];
            }
            B[j] = B[j] - d * B[k];
        }
    }

    #pragma omp parallel for
    for (int k = n - 1; k >= 0; k--)
    {
        double d = 0;
        for (int j = k + 1; j < n; j++)
            d += matr[k][j] * x[j];

        x[k] = (B[k] - d) / matr[k][k];
    }

    auto end = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "time : " << time.count() << " ms\n";

    // for (int i = 0; i < n; i++)
    //     cout << "x[" << i << "]=" << x[i] << " " << endl;

    return 0;
}
