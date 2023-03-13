#ifndef COMMS_MIDDLEWARE_FAKESUBSCRIBER_H
#define COMMS_MIDDLEWARE_FAKESUBSCRIBER_H

#include "CommsTypes.h"
#include "SubscriberImpl.h"
#include "ThreadSafeQueue.h"

#include <memory>
#include <thread>
#include <queue>
#include <atomic>

class FakePubSubBackend;

class FakeSubscriber: public SubscriberImpl {
public:
    FakeSubscriber(TopicIdentifier topicId,  FakePubSubBackend& provider);
    ~FakeSubscriber() override;

    Status Init() override;
    std::optional<Message> GetMessage() override;

private:
    friend FakePubSubBackend;
    std::atomic_bool m_initialized = false;
    ThreadSafeQueue<std::string> m_queue;

    FakePubSubBackend& m_provider;
    TopicIdentifier m_topicId;
};

#endif //COMMS_MIDDLEWARE_FAKESUBSCRIBER_H
