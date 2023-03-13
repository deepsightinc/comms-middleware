
#ifndef COMMS_MIDDLEWARE_ZMQPUBLISHER_H
#define COMMS_MIDDLEWARE_ZMQPUBLISHER_H


#include "CommsTypes.h"
#include "PublisherImpl.h"
#include "ThreadSafeQueue.h"

#include <memory>
#include <atomic>
#include <thread>

namespace zmq {
    class context_t;
    class socket_t;
}

class ZmqPublisher: public PublisherImpl {
public:
    ZmqPublisher(TopicName topic, IpAddress ipAddress, Port port, std::shared_ptr<zmq::context_t> context);
    ~ZmqPublisher() override;

    Status Init() override;
    Status Push(std::string msg) override;
private:
    void PublisherLoop();
    std::atomic_bool m_initialized = false;
    std::mutex m_initializeMutex;
    std::condition_variable m_initializeCv;

    IpAddress m_ip;
    Port m_port;
    TopicName m_topic;

    std::atomic_bool m_cancelThread = false;
    std::thread m_publisherThread;
    ThreadSafeQueue<std::string> m_queue;

    std::shared_ptr<zmq::context_t> m_context;
    std::unique_ptr<zmq::socket_t> m_socket;
};

#endif //COMMS_MIDDLEWARE_ZMQPUBLISHER_H
