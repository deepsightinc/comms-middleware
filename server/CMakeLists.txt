add_executable(server server.cpp)


target_compile_features(server PRIVATE cxx_std_17)
target_include_directories(server PRIVATE ../deps/popl)
target_link_libraries(server PRIVATE Comms)
