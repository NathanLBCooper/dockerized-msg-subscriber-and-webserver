#include "connectionHandler.hpp"

#include <exception>

namespace RabbitMqCppExample {

    ConnectionHandler::ConnectionHandler() {}

    void ConnectionHandler::onData(AMQP::Connection *connection, const char *data, size_t size) {
        throw std::runtime_error("not implemented");
    }

    void ConnectionHandler::onReady(AMQP::Connection *connection) {
        throw std::runtime_error("not implemented");
    }

    void ConnectionHandler::onError(AMQP::Connection *connection, const char *message) {
        throw std::runtime_error("not implemented");
    }

    void ConnectionHandler::onClosed(AMQP::Connection *connection) {
        throw std::runtime_error("not implemented");
    }
}
