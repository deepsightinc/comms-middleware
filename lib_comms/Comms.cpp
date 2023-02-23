
#include "Comms.h"
#include "zmq/ZmqPubSubBackend.h"

Comms::Comms(const Config& commsConfiguration) : m_config(commsConfiguration),
m_backend(std::make_unique<ZmqPubSubBackend>()){}

SubscriberPtr Comms::CreateSubscriber(const Topic& topic, const IpAddress& address, const Port& port) {
    return m_backend->CreateSubscriber(topic, address, port);
}

PublisherPtr Comms::CreatePublisher(const Topic& topic, const IpAddress& address, const Port& port) {
    return m_backend->CreatePublisher(topic, address, port);
}

Status Comms::Init() {
    return m_backend->Init();
}

