#include "server.hpp"

#include <string>

using namespace restinio;

http_server_t<my_traits_t> createServer(int port, std::string address, asio::io_context& ioContext);
std::unique_ptr<router::express_router_t<>> createRouter();

namespace RabbitMqCppExample {
    Server::Server() {
        _restinioServer = std::make_unique<http_server_t<my_traits_t>>(createServer(8080, "0.0.0.0", _ioContext));
    }

    void Server::openAsync(std::function<void(void)> serverStartedCallback, std::function<void(const std::exception_ptr)> errorCallback) {
        _serverThread = std::make_unique<std::thread>(std::thread([&] { _ioContext.run(); })); // start server thread
        _restinioServer->open_async(serverStartedCallback, errorCallback);
    }

    void Server::join() {
        _serverThread->join();
    }
}

http_server_t<my_traits_t> createServer(int port, std::string address, asio::io_context &ioContext) {
    restinio::http_server_t<my_traits_t> server {
        restinio::external_io_context(ioContext),
        [&]( auto & settings ){
            settings
            .port(port)
            .address(address)
            .request_handler(createRouter());
        }
    };

    return server;
}

std::unique_ptr<router::express_router_t<>> createRouter() {
    auto router = std::make_unique<router::express_router_t<>>();
    router->http_get(
            "/health",
            [](auto req, auto params) {
                return req->create_response().set_body("Okay").done();
            });


    router->non_matched_request_handler(
            [](auto req){
                return req->create_response(status_not_found()).connection_close().done();
            });

    return router;
}
