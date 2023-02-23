
#ifndef COMMS_MIDDLEWARE_ZMQPUBLISHER_H
#define COMMS_MIDDLEWARE_ZMQPUBLISHER_H


#include "CommsTypes.h"
#include "Publisher.h"

#include <memory>

namespace zmq {
    class context_t;
    class socket_t;
}

class ZmqPublisher: public Publisher {
public:
    ZmqPublisher(std::string ipAddress, int port);
    ~ZmqPublisher();

    Status Init() override;
    Status Push(std::string msg) override;
private:
    std::string m_ip;
    int m_port;

    std::unique_ptr<zmq::context_t> m_context;
    std::unique_ptr<zmq::socket_t> m_socket;
};

#endif //COMMS_MIDDLEWARE_ZMQPUBLISHER_H
