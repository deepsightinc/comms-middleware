//
// Created by manojv on 2/22/23.
//

#ifndef COMMS_MIDDLEWARE_COMMS_H
#define COMMS_MIDDLEWARE_COMMS_H

#include <unordered_map>
#include <string>

#include "Publisher.h"
#include "Subscriber.h"
#include "PubSubBackend.h"
#include "CommsTypes.h"

class Comms {
public:
    using Config = std::unordered_map<std::string, std::string>;
    Comms(const Config& commsConfiguration);

    Status Init();
    SubscriberPtr CreateSubscriber(const Topic& topic, const IpAddress& address, const Port& port);
    PublisherPtr CreatePublisher(const Topic& topic, const IpAddress& address, const Port& port);
private:
    const Config& m_config;
    PubSubBackendPtr m_backend = nullptr;
};

#endif //COMMS_MIDDLEWARE_COMMS_H
