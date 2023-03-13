add_executable(client client.cpp)
target_include_directories(client PRIVATE ../deps/popl)
target_link_libraries(client PRIVATE Comms)
