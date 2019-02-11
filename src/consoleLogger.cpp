#include <iostream>
#include <string>
#include "consoleLogger.hpp"

namespace RabbitMqExample
{
    ConsoleLogger::ConsoleLogger()
    {
    }

    void ConsoleLogger::log(std::string text)
    {
        std::cout << text << std::endl;
    }
}