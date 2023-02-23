#ifndef COMMS_MIDDLEWARE_ZMQSUBSCRIBER_H
#define COMMS_MIDDLEWARE_ZMQSUBSCRIBER_H

#include "CommsTypes.h"
#include "Subscriber.h"

#include <memory>

namespace zmq {
    class context_t;
    class socket_t;
}

class ZmqSubscriber: public Subscriber {
public:
    ZmqSubscriber(std::string ipAddress, int port);
    ~ZmqSubscriber();

    Status Init() override;
    std::optional<Message> GetMessage() override;
    std::optional<Messages> GetMessages() override;
private:
    std::string m_ip;
    int m_port;

    std::unique_ptr<zmq::context_t> m_context;
    std::unique_ptr<zmq::socket_t> m_socket;
};

#endif //COMMS_MIDDLEWARE_ZMQSUBSCRIBER_H
