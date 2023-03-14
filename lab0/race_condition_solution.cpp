#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<unsigned long long> x { 0 };

void inc()
{
    for(int i = 0; i < 1000000; i++)
        x.fetch_add(1);
}

int main()
{

    thread t1(inc);
    thread t2(inc);
    
    t1.join();
    t2.join();
    
    cout << x;

    return 0;
}