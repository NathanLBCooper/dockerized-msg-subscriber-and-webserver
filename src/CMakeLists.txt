cmake_minimum_required(VERSION 3.0.0)
project(rabbitmqcppexample
            VERSION 0.1.0
            DESCRIPTION "Nathan is trying to figure shit out")

find_package(Threads)
find_package(Catch2 REQUIRED)
find_package(fmt REQUIRED)
find_package(unofficial-http-parser REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(restinio REQUIRED)

set(sources
    main.cpp
    server.cpp
)
add_executable(rabbitmqcppexample ${sources})
target_link_libraries(
    rabbitmqcppexample
    PRIVATE
        ${CMAKE_THREAD_LIBS_INIT}
        fmt::fmt
        unofficial::http_parser::http_parser
        ${Boost_LIBRARIES}
        restinio::restinio
)
set_property(TARGET rabbitmqcppexample
    PROPERTY CXX_STANDARD 17)


set(testsources
    catch_test.cpp
    foo_test.cpp
)
add_executable(tests ${testsources})
set_property(TARGET tests
    PROPERTY CXX_STANDARD 17)
target_link_libraries(
    tests
    PRIVATE
        Catch2::Catch2
)

enable_testing()
include(CTest)
include(Catch)
catch_discover_tests(tests)
