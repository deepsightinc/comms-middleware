#ifndef COMMS_MIDDLEWARE_ZMQSUBSCRIBER_H
#define COMMS_MIDDLEWARE_ZMQSUBSCRIBER_H

#include "CommsTypes.h"
#include "Subscriber.h"
#include "ThreadSafeQueue.h"

#include <memory>
#include <thread>
#include <queue>
#include <atomic>

namespace zmq {
    class context_t;
    class socket_t;
}

class ZmqSubscriber: public Subscriber {
public:
    ZmqSubscriber(std::string ipAddress, int port, std::shared_ptr<zmq::context_t> context);
    ~ZmqSubscriber();

    Status Init() override;
    std::optional<Message> GetMessage() override;
private:
    void SubscriberLoop();
    std::string m_ip;
    int m_port;

    std::shared_ptr<zmq::context_t> m_context;

    std::atomic_bool m_cancelThread = false;
    std::thread m_subscriberThread;
    ThreadSafeQueue<std::string> m_queue;
};

#endif //COMMS_MIDDLEWARE_ZMQSUBSCRIBER_H
