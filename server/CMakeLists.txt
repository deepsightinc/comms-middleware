add_executable(app main.cpp)
target_compile_features(app PRIVATE cxx_std_17)
target_include_directories(app PRIVATE ../deps/popl)

#target_link_libraries(app PRIVATE modern_library fmt::fmt)
