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

    PublisherImplPtr CreatePublisher(const TopicName& topic, const IpAddress& address, const Port& port) override;
    SubscriberImplPtr CreateSubscriber(const TopicName& topic, const IpAddress& address, const Port& port) override;
private:
    std::shared_ptr<zmq::context_t> m_sharedContext;
};

#endif //COMMS_MIDDLEWARE_ZMQPUBSUBBACKEND_H
