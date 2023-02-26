#ifndef COMMS_MIDDLEWARE_ZMQPUBSUBBACKEND_H
#define COMMS_MIDDLEWARE_ZMQPUBSUBBACKEND_H

#include "PubSubBackend.h"
#include "CommsTypes.h"

namespace zmq {
    class context_t;
}

class ZmqPubSubBackend: public PubSubBackend {
public:
    ZmqPubSubBackend();
    ~ZmqPubSubBackend() override = default;

    Status Init() override;
    PublisherPtr CreatePublisher(const Topic& topic, const IpAddress& address, const Port& port) override;
    SubscriberPtr CreateSubscriber(const Topic& topic, const IpAddress& address, const Port& port) override;
private:
    std::shared_ptr<zmq::context_t> m_sharedContext;
};

#endif //COMMS_MIDDLEWARE_ZMQPUBSUBBACKEND_H
