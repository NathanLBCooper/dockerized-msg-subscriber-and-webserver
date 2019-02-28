#include <iostream>
#include <thread>
#include <exception>
#include <stdexcept>
#include <vector>

#include "server/server.hpp"

using namespace RabbitMqCppExample;

int main() {
    try {
        Server server;
        server.openAsync(
            // Ok callback. Nothing to do.
            []{},
            // Error callback. Rethrow an exception.
            []( auto ex_ptr ) {
                std::rethrow_exception( ex_ptr );
            }
        );

        server.join();
    }
    catch (const std::exception & ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
