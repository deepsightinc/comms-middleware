#include "FakePubSubBackend.h"
#include "FakePublisher.h"
#include "FakeSubscriber.h"

#include <algorithm>
#include <iostream>


SubscriberImplPtr FakePubSubBackend::CreateSubscriber(const TopicName& topic, const IpAddress& address, const Port& port) {
    TopicIdentifier topicId = std::make_tuple(topic, address, port);
    return std::make_unique<FakeSubscriber>(topicId, *this);
}

PublisherImplPtr FakePubSubBackend::CreatePublisher(const TopicName& topic, const IpAddress& address, const Port& port) {
    TopicIdentifier topicId = std::make_tuple(topic, address, port);
    return std::make_unique<FakePublisher>(topicId, *this);
}

Status FakePubSubBackend::Init() {
    return Status::OK;
}

void FakePubSubBackend::PushMessageData(TopicIdentifier identifier, std::string messageData) {
    std::lock_guard<std::mutex> lg(m_pubSubLock);

    for(const auto& topicListenersPair : m_pubSubMap) {
        bool topicMatches = (std::get<0>(topicListenersPair.first) == std::get<0>(identifier));
        // Server wildcard IP binds to all IPs present on system.
        bool ipMatches = std::get<1>(identifier) == "*" || (std::get<1>(topicListenersPair.first) == std::get<1>(identifier));
        bool portMatches = (std::get<2>(topicListenersPair.first) == std::get<2>(identifier));

        if(!(topicMatches && portMatches && ipMatches)) {
            continue;
        }

        for(auto* subscriber : topicListenersPair.second) {
            subscriber->m_queue.push(messageData);
        }
    }
}

void FakePubSubBackend::RegisterSubscriber(TopicIdentifier identifier, FakeSubscriber* subscriber) {
    std::lock_guard<std::mutex> lg(m_pubSubLock);
    m_pubSubMap[identifier].push_back(subscriber);
}

void FakePubSubBackend::UnregisterSubscriber(TopicIdentifier identifier, FakeSubscriber* removeSubscriber) {
    std::lock_guard<std::mutex> lg(m_pubSubLock);
    m_pubSubMap[identifier].erase(std::remove_if(m_pubSubMap[identifier].begin(), m_pubSubMap[identifier].end(),
        [removeSubscriber](FakeSubscriber* subscriberPtr){
        return subscriberPtr == removeSubscriber;
    }), 
        m_pubSubMap[identifier].end());
}

