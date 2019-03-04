#include <iostream>
#include <thread>
#include <exception>
#include <stdexcept>
#include <vector>

#include "server/server.hpp"
#include "taskDiagnostic.hpp"
#include "worker/worker.hpp"

using namespace RabbitMqCppExample;

int main() {
    try {
        std::vector<TaskDiagnostic> tasks;

        tasks.push_back(TaskDiagnostic("Diagnostic Server", Status::starting));
        TaskDiagnostic &serverTask = tasks.back();

        ApplicationDependencies dependencies (&tasks);
        Server server(dependencies);
        server.openAsync(
            [&serverTask]{ 
                serverTask.status = Status::running;
            },
            [&serverTask]( auto ex_ptr ) {
                serverTask.status = Status::failed;
                std::rethrow_exception( ex_ptr );
            }
        );

        tasks.push_back(TaskDiagnostic("Worker", Status::starting));
        TaskDiagnostic &listenerTask = tasks.back();

        Worker worker;
        worker.listenAsync(
            [&listenerTask]{ 
                listenerTask.status = Status::running;
            },
            [&listenerTask]( auto ex_ptr ) {
                listenerTask.status = Status::failed;
                try {
                    std::rethrow_exception (ex_ptr);
                } catch (const std::exception& e) {
                    listenerTask.reason = e.what();
                }        
            }
        );

        worker.join();
        server.join();
    }
    catch (const std::exception & ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
