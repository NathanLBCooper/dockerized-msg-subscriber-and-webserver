#pragma once

#include <exception>
#include <functional>
#include <memory>
#include <boost/asio/io_service.hpp>
#include <boost/thread/thread.hpp>
#include <amqpcpp.h>
#include <amqpcpp/libboostasio.h>

namespace RabbitMqCppExample {
    class Worker final
    {
        private:
            boost::asio::io_service _ioService;
            boost::asio::io_service::work _ioWork;
            AMQP::LibBoostAsioHandler _handler;
            AMQP::Address _address;
            std::unique_ptr<AMQP::TcpConnection> _connection;
            std::unique_ptr<AMQP::TcpChannel> _channel;
            std::unique_ptr<boost::thread> _workerThread;
            void listen();
        public:
            explicit Worker();
            void listenAsync(std::function<void(void)> listenerStartedCallback, std::function<void(const std::exception_ptr)> errorCallback);
            void join();
    };
};
