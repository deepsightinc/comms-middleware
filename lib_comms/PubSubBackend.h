#ifndef COMMS_MIDDLEWARE_PUBSUBBACKEND_H
#define COMMS_MIDDLEWARE_PUBSUBBACKEND_H

#include "PublisherImpl.h"
#include "SubscriberImpl.h"
#include "CommsTypes.h"

class PubSubBackend {
public:
    virtual ~PubSubBackend() = default;
    
    virtual Status Init() = 0;

    virtual PublisherImplPtr CreatePublisher(const TopicName& topic, const IpAddress& address, const Port& port) = 0;
    virtual SubscriberImplPtr CreateSubscriber(const TopicName& topic, const IpAddress& address, const Port& port) = 0;
};
using PubSubBackendPtr = std::unique_ptr<PubSubBackend>;

#endif //COMMS_MIDDLEWARE_PUBSUBBACKEND_H
