cmake_minimum_required(VERSION 3.0)

project(comms-middleware)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_RPATH "/usr/local/lib")

## load in pkg-config support
find_package(PkgConfig)
## use pkg-config to get hints for 0mq locations
pkg_check_modules(PC_ZeroMQ QUIET zmq)

## use the hint from above to find where 'zmq.hpp' is located
find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

## use the hint from above to find the location of libzmq
find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )




add_subdirectory(lib_comms)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(test)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
