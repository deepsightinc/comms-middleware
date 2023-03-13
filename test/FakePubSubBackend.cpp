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
    auto matchedSubscribersIter = std::find_if(m_pubSubMap.begin(), m_pubSubMap.end(),
                                           [identifier](const std::pair<TopicIdentifier, std::vector<FakeSubscriber*>>& somePair){
        bool topicMatches = (std::get<0>(somePair.first) == std::get<0>(identifier));
        bool portMatches = (std::get<2>(somePair.first) == std::get<2>(identifier));
        bool ipMatches = std::get<1>(identifier) == "*" || (std::get<1>(somePair.first) == std::get<1>(identifier));

        return topicMatches && portMatches && ipMatches;
    });

    while(matchedSubscribersIter != m_pubSubMap.end()) {
        for(auto* subscriber : m_pubSubMap.at((*matchedSubscribersIter).first)) {
            subscriber->m_queue.push(messageData);
        }
        std::advance(matchedSubscribersIter, 1);
    }
}

void FakePubSubBackend::RegisterSubscriber(TopicIdentifier identifier, FakeSubscriber* subscriber) {
//    if(m_pubSubMap.find(identifier) == m_pubSubMap.end()) {
//        m_pubSubMap[identifier] = {};
//    }
    m_pubSubMap[identifier].push_back(subscriber);
    std::cout << "reg" << std::endl;
}

void FakePubSubBackend::UnregisterSubscriber(TopicIdentifier identifier, FakeSubscriber* removeSubscriber) {
    m_pubSubMap[identifier].erase(std::remove_if(m_pubSubMap[identifier].begin(), m_pubSubMap[identifier].end(), 
        [removeSubscriber](FakeSubscriber* subscriberPtr){
        return subscriberPtr == removeSubscriber;
    }), 
        m_pubSubMap[identifier].end());
}

