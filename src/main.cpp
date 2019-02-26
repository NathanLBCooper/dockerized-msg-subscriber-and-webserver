#include <iostream>
#include <thread>
#include <exception>
#include <stdexcept>

#include "server.hpp"

using namespace RabbitMqCppExample;

std::thread runServer(std::exception_ptr& exceptionPtr);

int main(){
    try {
        std::exception_ptr serverExceptionPtr = nullptr;
        auto serverThread = runServer(serverExceptionPtr);

        serverThread.join();

        if (serverExceptionPtr) {
            std::rethrow_exception(serverExceptionPtr);
        }
    }
    catch (const std::exception & ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

std::thread runServer(std::exception_ptr& exceptionPtr) {
    std::thread serverThread([&exceptionPtr]() {
        try {
            Server server;
            server.run();
        }
        catch (const std::exception & ex)
        {
            exceptionPtr = std::current_exception();
        }
    });

    return serverThread;
}