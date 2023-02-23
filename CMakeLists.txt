cmake_minimum_required(VERSION 3.0)

project(comms-middleware)
# using C++ 17
set(CMAKE_CXX_STANDARD 17)


#add_subdirectory(lib_comms)
add_subdirectory(client)
add_subdirectory(server)
#add_subdirectory(comms)

set(CMAKE_DISABLE_IN_SOURCE_BUILD OFF)
