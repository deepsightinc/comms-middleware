add_executable(server main.cpp)
target_compile_features(server PRIVATE cxx_std_17)
target_include_directories(server PRIVATE ../deps/popl)