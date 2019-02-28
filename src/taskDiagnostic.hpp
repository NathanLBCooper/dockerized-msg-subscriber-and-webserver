#pragma once

#include <string>

namespace RabbitMqCppExample {

    enum Status {
        unstarted,
        starting,
        running,
        failed,
        stopped
    };

    class TaskDiagnostic final
    {
        public:
            TaskDiagnostic() {};
            TaskDiagnostic(std::string name, Status status, std::string reason = "") { 
                this->name = name;
                this->status = status;
                this->reason = reason;
            };
            std::string name;
            Status status;
            std::string reason;
            std::string getStatusString() {
                switch (status)
                {
                    case Status::unstarted:
                        return "Unstarted";
                    case Status::starting:
                        return "Starting";
                    case Status::running:
                        return "Running";
                    case Status::failed:
                        return "Failed";
                    case Status::stopped:
                        return "Stopped";
                    default:
                        return "Unknown";
                }
            }
    };
}