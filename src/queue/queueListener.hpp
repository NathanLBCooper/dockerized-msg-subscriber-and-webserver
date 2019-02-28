#pragma once

#include <exception>
#include <functional>

namespace RabbitMqCppExample {
    class QueueListener final
    {
        public:
            explicit QueueListener();
            void listenAsync(std::function<void(void)> listenerStartedCallback, std::function<void(const std::exception_ptr)> errorCallback);
            void join();
    };
};
