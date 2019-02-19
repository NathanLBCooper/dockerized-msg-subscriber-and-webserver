cmake_minimum_required(VERSION 3.0.0)
project(rabbitmqcppexample VERSION 0.1.0)

# include(CTest)
# enable_testing()

file(GLOB sources src/**.cpp src/**.c)  # todo filter out catch stuffs
add_executable(rabbitmqcppexample ${sources})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
