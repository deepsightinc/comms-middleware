enable_testing()

find_package(GTest REQUIRED)

set(HEADER_LIST
        FakePublisher.h
        FakeSubscriber.h
        FakePubSubBackend.h
        )

set(SOURCE_LIST
        FakePublisher.cpp
        FakeSubscriber.cpp
        FakePubSubBackend.cpp)

add_library(Comms_testing ${SOURCE_LIST} ${HEADER_LIST})
target_link_libraries(Comms_testing PUBLIC Comms)
target_include_directories(Comms_testing PUBLIC ./)


add_executable(unit_tests test_middleware.cpp)
target_link_libraries(unit_tests PRIVATE Comms Comms_testing)
target_link_libraries(unit_tests PRIVATE GTest::gtest)

