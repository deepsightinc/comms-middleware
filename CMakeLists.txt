cmake_minimum_required(VERSION 3.0)

project(comms-middleware)
set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)

add_subdirectory(lib_comms)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(test)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
