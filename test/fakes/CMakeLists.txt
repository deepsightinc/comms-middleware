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
