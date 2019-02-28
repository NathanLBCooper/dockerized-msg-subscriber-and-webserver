#include "queueListener.hpp"

extern "C" {
    #include <amqp.h>
    #include <amqp_tcp_socket.h>
}
#include <memory>

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
        // https://github.com/alanxz/rabbitmq-c/blob/master/examples/amqp_listen.c

        // std::string hostname("0.0.0.0");
        // int port(8000);

        // amqp_connection_state_t conn (amqp_new_connection());

        // std::unique_ptr<amqp_socket_t> socket = std::make_unique<amqp_socket_t>(amqp_tcp_socket_new(conn));

        // if (!socket) {
        //     throw std::runtime_error("Failed to create TCP socket");
        // }

        // int status = amqp_socket_open(socket.get(), hostname.c_str(), port);

        // if (status == 0) {
        //     throw std::runtime_error("Failed to open TCP socket");
        // }

        throw std::runtime_error("not implemented");

        // todo make throw version of die_on_amqp_error
    }
}