cmake_minimum_required(VERSION 3.0.0)
project(rabbitmqcppexample
            VERSION 0.1.0
            DESCRIPTION "Nathan is trying to figure shit out")

set(sources
    server.cpp
)

add_executable(rabbitmqcppexample ${sources})

# find_package(something REQUIRED)
# find_package(somethingelse REQUIRED COMPONENTS somecomponent)

# target_link_libraries(
#     rabbitmqcppexample
#     PRIVATE
#         # stuff
# )

set_property(TARGET rabbitmqcppexample
                PROPERTY CXX_STANDARD 17)
