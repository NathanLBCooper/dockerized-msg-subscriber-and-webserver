#include "worker.hpp"

#include <memory>
#include <string>
#include <iostream> // todo
#include <boost/bind.hpp>

namespace RabbitMqCppExample {

    Worker::Worker(): _ioService(1), _ioWork(_ioService), _handler(_ioService), _address("amqp://guest:guest@192.168.65.2/") {
    }

    void Worker::listenAsync(std::function<void(void)> workerStartedCallback, std::function<void(const std::exception_ptr)> errorCallback) {
        
        try {
            listen();
            // todo success callback in listen
            workerStartedCallback();
        } catch (const std::exception & ex) {
            errorCallback(std::make_exception_ptr(ex));
        }
    }

    void Worker::join() {
        _workerThread->join();
    }

    void Worker::listen() {

        // // todo host.docker.internal, myinput etc
        _connection = std::make_unique<AMQP::TcpConnection>(&_handler, _address);
        _channel = std::make_unique<AMQP::TcpChannel>(_connection.get());

        _channel->consume("myinput", AMQP::noack)
            .onReceived([](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {
                    std::cout << "recieved message: '" << message.body() << std::endl;
                }
            )
            .onError([](const std::string message) {
                    std::cout << "error recieving: " << message << std::endl;
                }
            );

        _workerThread = std::make_unique<boost::thread>([](boost::asio::io_service *ioS) {
            // todo exceptions after this point
            return ioS->run();
        }, &_ioService);
    }
}
