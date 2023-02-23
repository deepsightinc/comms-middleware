#include "zmq/ZmqPubSubBackend.h"
#include "zmq/ZmqPublisher.h"
#include "zmq/ZmqSubscriber.h"


SubscriberPtr ZmqPubSubBackend::CreateSubscriber(const Topic& topic, const IpAddress& address, const Port& port) {
    return std::make_unique<ZmqSubscriber>(address, port);
}

PublisherPtr ZmqPubSubBackend::CreatePublisher(const Topic& topic, const IpAddress& address, const Port& port) {
    return std::make_unique<ZmqPublisher>(address, port);
}

Status ZmqPubSubBackend::Init() {
    return Status::OK;
}

