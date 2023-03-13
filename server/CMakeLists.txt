add_executable(server server.cpp)

target_include_directories(server PRIVATE ../deps/popl)
target_link_libraries(server PRIVATE Comms)
