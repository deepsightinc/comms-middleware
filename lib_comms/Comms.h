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

#include "zmq/ZmqPubSubBackend.h"


class Comms {
public:
    Comms() : m_ownedBackend(std::make_unique<ZmqPubSubBackend>()),
        m_backend(*m_ownedBackend){}

    Comms(PubSubBackend& backend) : m_backend(backend){}

    Status Init() {
        return m_backend.Init();
    }

    template<typename Topic, typename TopicType = typename Topic::payloadType>
    SubscriberPtr<TopicType> CreateSubscriber( const IpAddress& address, const Port& port) {
        auto subscriberImpl = m_backend.CreateSubscriber(Topic::GetName(), address, port);
        SubscriberPtr<TopicType> newSubscriber = std::make_unique<Subscriber<TopicType>>(std::move(subscriberImpl));
        return newSubscriber;
    }

    template<typename Topic, typename TopicType = typename Topic::payloadType>
    PublisherPtr<TopicType> CreatePublisher( const IpAddress& address, const Port& port) {
        auto publisherImpl = m_backend.CreatePublisher(Topic::GetName(), address, port);
        PublisherPtr<TopicType> newPublisher = std::make_unique<Publisher<TopicType>>(std::move(publisherImpl));
        return newPublisher;
    }

private:
    PubSubBackendPtr m_ownedBackend = nullptr;
    PubSubBackend& m_backend;
};







#endif //COMMS_MIDDLEWARE_COMMS_H
