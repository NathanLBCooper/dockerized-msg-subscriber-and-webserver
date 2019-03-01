#include "queueListener.hpp"

#include <amqpcpp.h>
#include <memory>

#include "connectionHandler.hpp"

namespace RabbitMqCppExample {
    void listen();

    QueueListener::QueueListener() {}

    void QueueListener::listenAsync(std::function<void(void)> listenerStartedCallback, std::function<void(const std::exception_ptr)> errorCallback) {
        
        errorCallback(std::make_exception_ptr(std::runtime_error("not implemented")));
        
        // todo not in any way async
        try {
            listen();
        } catch (const std::exception & ex) {
            errorCallback(std::make_exception_ptr(ex));
        }
    }

    void QueueListener::join() {
        // todo
    }

    void listen() {

        ConnectionHandler handler;

        //AMQP::Connection connection(&handler, AMQP::Login("guest","guest"), "/");
        //AMQP::Channel channel(&connection);

        throw std::runtime_error("not implemented");
    }
}
