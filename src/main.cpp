#include <amqp.h>
#include <amqp_tcp_socket.h>

#include "consoleLogger.hpp"

using namespace RabbitMqExample;

int main(){
    ConsoleLogger logger;
    
    amqp_connection_state_t conn;

    conn = amqp_new_connection();
    amqp_destroy_connection(conn);

    return 1;
}
