enable_testing()

add_subdirectory(fakes)

find_package(GTest REQUIRED)

add_executable(unit_tests test_middleware.cpp)
target_link_libraries(unit_tests PRIVATE Comms Comms_testing)
target_link_libraries(unit_tests PRIVATE GTest::gtest)

