set(HEADER_LIST
        Comms.h
        CommsTypes.h
        Publisher.h
        Subscriber.h
        PubSubBackend.h
        zmq/ZmqPublisher.h
        zmq/ZmqPubSubBackend.h
        zmq/ZmqSubscriber.h
        ThreadSafeQueue.h Topics.h)

set(SOURCE_LIST
        Comms.cpp
        zmq/ZmqPublisher.cpp
        zmq/ZmqSubscriber.cpp
        zmq/ZmqPubSubBackend.cpp)

## load in pkg-config support
find_package(PkgConfig)
## use pkg-config to get hints for 0mq locations
pkg_check_modules(PC_ZeroMQ QUIET zmq)

## use the hint from above to find where 'zmq.hpp' is located
find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

## use the hint from above to find the location of libzmq
find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )

add_library(Comms ${SOURCE_LIST} ${HEADER_LIST})
target_link_libraries(Comms PUBLIC ${ZeroMQ_LIBRARY})
target_include_directories(Comms PUBLIC ./)
