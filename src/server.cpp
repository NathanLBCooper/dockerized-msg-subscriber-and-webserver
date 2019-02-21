#include "server.hpp"

#include <iostream>
#include <restinio/all.hpp>

using namespace restinio;

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

int main() {
    try {
        struct my_server_traits : public default_single_thread_traits_t {
            using request_handler_t = restinio::router::express_router_t<>;
        };

        restinio::run(
                restinio::on_this_thread<my_server_traits>()
                        .port(8080)
                        .address("0.0.0.0")
                        .request_handler(createRouter()));
    }
    catch (const std::exception & ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}