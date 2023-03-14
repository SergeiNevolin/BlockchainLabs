#include <iostream>
#include <mutex>
#include <thread>

std::mutex m1;
std::mutex m2;

void f1()
{
    std::lock_guard<std::mutex> lg1(m1);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::lock_guard<std::mutex> lg2(m2);
}

void f2()
{
    std::lock_guard<std::mutex> lg1(m2);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::lock_guard<std::mutex> lg2(m1);
}

int main()
{
    std::thread thread1(f1);
    
    std::thread thread2(f2);
    
    thread1.join();
    thread2.join();

    return 0;
}