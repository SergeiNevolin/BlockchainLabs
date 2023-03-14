#include <iostream>
#include <chrono>
using namespace std;
 

const int ARR_SIZE = 1'000'000'000;

void SumArray(int* arr, int step)
{
    auto begin = chrono::steady_clock::now();

    unsigned long long sum = 0;
    for(int i = 0; i < ARR_SIZE; i += step)
    {
        sum += arr[i];
    }

    cout << "Sum = " << sum << ", with step: " << step << ", ";

    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "time: " << elapsed_ms.count() << " ms, ";
    cout << "average time: " << elapsed_ms.count() / (ARR_SIZE * 1.0 / step) << " ms\n";
}

int main()
{
    int* Arr = new int[ARR_SIZE]; 

    int num;
    for(int i = 0; i < ARR_SIZE; i++)
    {
        Arr[i] = rand();
    }

    SumArray(Arr, 1);
    SumArray(Arr, 2);
    SumArray(Arr, 4);
    SumArray(Arr, 8);
    SumArray(Arr, 16);
    SumArray(Arr, 32);

}