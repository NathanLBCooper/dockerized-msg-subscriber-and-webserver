#include <iostream>
#include <mutex>

#include "server.hpp"

int main()
{
    // Print
    std::cout << "hey, here's some stdout" << std::endl;

    // Then sleep forever in an evil way
    std::mutex m;
    m.lock();
    m.lock();

    return 0;
}