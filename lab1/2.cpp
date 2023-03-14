#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;
 

const int ARR_SIZE = 1'000'000'000;

void CountPositive(int* arr)
{
    auto begin = chrono::steady_clock::now();

    int count = 0;
    for(int i = 0; i < ARR_SIZE; i++)
    {
        if (arr[i] > 0)
            count++;

    }
    
    cout << "Count " << count << "\n";

    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "time: " << elapsed_ms.count() << " ms\n";
}

int main()
{
    int* Arr = new int[ARR_SIZE]; 

    int num;
    for(int i = 0; i < ARR_SIZE; i++)
    {
        Arr[i] = rand() - RAND_MAX/2;
    }

    cout << "Count positive numbers without sort \n";
    CountPositive(Arr);

    cout << "Count positive numbers with sort \n";
    sort(Arr, Arr + ARR_SIZE);
    CountPositive(Arr);

}