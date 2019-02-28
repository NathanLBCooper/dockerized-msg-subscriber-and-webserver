#pragma once

#include <exception>
#include <functional>
#include <memory>
#include <thread>
#include <restinio/all.hpp>

using my_traits_t = restinio::traits_t<
    restinio::asio_timer_manager_t,
    restinio::single_threaded_ostream_logger_t,
    restinio::router::express_router_t<>>;

namespace RabbitMqCppExample {
    class Server final
    {
        private:
            std::unique_ptr<restinio::http_server_t<my_traits_t>> _restinioServer;
            std::unique_ptr<std::thread> _serverThread;
            asio::io_context _ioContext;
        public:
            explicit Server();
            void openAsync(std::function<void(void)> serverStartedCallback, std::function<void(const std::exception_ptr)> errorCallback);
            void join();
    };
};
