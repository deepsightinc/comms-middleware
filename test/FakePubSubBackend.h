#ifndef COMMS_MIDDLEWARE_FAKEPUBSUBBACKEND_H
#define COMMS_MIDDLEWARE_FAKEPUBSUBBACKEND_H

#include "PubSubBackend.h"
#include "CommsTypes.h"
#include "ThreadSafeQueue.h"

#include <unordered_map>
#include <mutex>

class FakeSubscriber;

class FakePubSubBackend: public PubSubBackend {
public:
    ~FakePubSubBackend() override = default;

    Status Init() override;

    PublisherImplPtr CreatePublisher(const TopicName& topic, const IpAddress& address, const Port& port) override;
    SubscriberImplPtr CreateSubscriber(const TopicName& topic, const IpAddress& address, const Port& port) override;

    void PushMessageData(TopicIdentifier identifier, std::string messageData);
    void RegisterSubscriber(TopicIdentifier identifier, FakeSubscriber* subscriber);
    void UnregisterSubscriber(TopicIdentifier identifier, FakeSubscriber* messageData);
private:
    struct tuple_key_hash : public std::unary_function<TopicIdentifier, std::size_t>
    {
        std::size_t operator()(const TopicIdentifier& key) const
        {
            std::size_t topicHash = std::hash<std::string>{}(std::get<0>(key));
            std::size_t ipHash = std::hash<std::string>{}(std::get<0>(key));
            std::size_t portHash = std::hash<std::string>{}(std::get<0>(key));
            return topicHash ^ (ipHash << 1) ^ (portHash << 2);
        }
    };
    std::mutex m_pubSubLock;
    std::unordered_map<TopicIdentifier, std::vector<FakeSubscriber*>, tuple_key_hash> m_pubSubMap; 
};

#endif //COMMS_MIDDLEWARE_FAKEPUBSUBBACKEND_H
