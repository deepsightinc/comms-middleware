set(HEADER_LIST
        Comms.h
        CommsTypes.h
        Publisher.h
        Subscriber.h
        PubSubBackend.h
        zmq/ZmqPublisher.h
        zmq/ZmqPubSubBackend.h
        zmq/ZmqSubscriber.h)

set(SOURCE_LIST
        Comms.cpp
        zmq/ZmqPublisher.cpp
        zmq/ZmqSubscriber.cpp
        zmq/ZmqPubSubBackend.cpp)


add_library(Comms ${SOURCE_LIST} ${HEADER_LIST})
target_link_libraries(Comms PUBLIC ${ZeroMQ_LIBRARY})
target_include_directories(Comms PUBLIC ./)
