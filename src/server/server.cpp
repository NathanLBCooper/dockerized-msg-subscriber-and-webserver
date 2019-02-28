#include "server.hpp"

#include <string>

using namespace restinio;

namespace RabbitMqCppExample {

    http_server_t<my_traits_t> createServer(int port, std::string address, asio::io_context& ioContext, ApplicationDependencies &dependencies);
    std::unique_ptr<router::express_router_t<>> createRouter(ApplicationDependencies &dependencies);
    std::string makeHealthResponseBody(ApplicationDependencies &dependencies);

    Server::Server(ApplicationDependencies &dependencies) {
        _restinioServer = std::make_unique<http_server_t<my_traits_t>>(createServer(8080, "0.0.0.0", _ioContext, dependencies));
    }

    void Server::openAsync(std::function<void(void)> serverStartedCallback, std::function<void(const std::exception_ptr)> errorCallback) {
        _serverThread = std::make_unique<std::thread>(std::thread([&] { _ioContext.run(); })); // start server thread
        _restinioServer->open_async(serverStartedCallback, errorCallback);
    }

    void Server::join() {
        _serverThread->join();
    }

    http_server_t<my_traits_t> createServer(int port, std::string address, asio::io_context &ioContext, ApplicationDependencies &dependencies) {
    restinio::http_server_t<my_traits_t> server {
            restinio::external_io_context(ioContext),
            [&]( auto & settings ){
                settings
                .port(port)
                .address(address)
                .request_handler(createRouter(dependencies));
            }
        };

        return server;
    }

    std::unique_ptr<router::express_router_t<>> createRouter(ApplicationDependencies &dependencies) {
        auto router = std::make_unique<router::express_router_t<>>();
        router->http_get(
                "/health",
                [&dependencies](auto req, auto params) {
                    return req->create_response().set_body(makeHealthResponseBody(dependencies)).done();
                });


        router->non_matched_request_handler(
                [](auto req){
                    return req->create_response(status_not_found()).connection_close().done();
                });

        return router;
    }

    std::string makeHealthResponseBody(ApplicationDependencies &dependencies) {
        // Crude health statment. Json would be better.
        std::string responseStr = "Okay. \n Running tasks:";
        for (auto task : *dependencies.tasks) {
            responseStr += "\n Name: " + task.name + ", Status: " + task.getStatusString();
            if (!task.reason.empty()) {
                responseStr += ", Reason: " + task.reason;
            }
        }

        return responseStr;
    }
}
