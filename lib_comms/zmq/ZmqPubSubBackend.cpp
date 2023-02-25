#include "zmq/ZmqPubSubBackend.h"
#include "zmq/ZmqPublisher.h"
#include "zmq/ZmqSubscriber.h"

#include "zmq.hpp"

ZmqPubSubBackend::ZmqPubSubBackend() : m_sharedContext(std::make_shared<zmq::context_t>()) {}

SubscriberPtr ZmqPubSubBackend::CreateSubscriber(const Topic& topic, const IpAddress& address, const Port& port) {
    return std::make_unique<ZmqSubscriber>(address, port, m_sharedContext);
}

PublisherPtr ZmqPubSubBackend::CreatePublisher(const Topic& topic, const IpAddress& address, const Port& port) {
    return std::make_unique<ZmqPublisher>(address, port, m_sharedContext);
}

Status ZmqPubSubBackend::Init() {
    return Status::OK;
}

