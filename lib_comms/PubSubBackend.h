//
// Created by manojv on 2/22/23.
//

#ifndef COMMS_MIDDLEWARE_PUBSUBBACKEND_H
#define COMMS_MIDDLEWARE_PUBSUBBACKEND_H

#include "Publisher.h"
#include "Subscriber.h"
#include "CommsTypes.h"

class PubSubBackend {
public:
    virtual Status Init() = 0;
    virtual PublisherPtr CreatePublisher(const Topic& topic, const IpAddress& address, const Port& port) = 0;
    virtual SubscriberPtr CreateSubscriber(const Topic& topic, const IpAddress& address, const Port& port) = 0;
};
using PubSubBackendPtr = std::unique_ptr<PubSubBackend>;

#endif //COMMS_MIDDLEWARE_PUBSUBBACKEND_H
