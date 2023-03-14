// #include <iostream>
// #include <thread>
// #include <assert.h>
// #include <atomic>
// using namespace std;

// int x = 0;
// // static std::atomic<int> x{ 0 };

// void foo()
// {
//     while (true)
//     {
//         x += 1;
//         x -= 1;
//         // x.fetch_add(1);
//         // x.fetch_add(-1);
//         assert(x == 0);
//     }
// }

// int main()
// {
//     thread t(foo);
//     thread t2(foo);
    
//     t.join();
//     t2.join();

//     cout << x;

//     return 0;
// }


#include <iostream>
#include <thread>
using namespace std;

unsigned long long x = 0;

void inc()
{
    for(int i = 0; i < 1000000; i++)
        x++;
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