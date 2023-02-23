#ifndef COMMS_MIDDLEWARE_ZMQPUBSUBBACKEND_H
#define COMMS_MIDDLEWARE_ZMQPUBSUBBACKEND_H

#include "PubSubBackend.h"
#include "CommsTypes.h"

class ZmqPubSubBackend: public PubSubBackend {
public:
     Status Init() override;
     PublisherPtr CreatePublisher(const Topic& topic, const IpAddress& address, const Port& port) override;
     SubscriberPtr CreateSubscriber(const Topic& topic, const IpAddress& address, const Port& port) override;
};

#endif //COMMS_MIDDLEWARE_ZMQPUBSUBBACKEND_H
