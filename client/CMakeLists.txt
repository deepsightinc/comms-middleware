add_executable(client main.cpp)
target_compile_features(client PRIVATE cxx_std_17)
target_include_directories(client PRIVATE ../deps/popl)