
#ifndef COMMS_MIDDLEWARE_FAKEPUBLISHER_H
#define COMMS_MIDDLEWARE_FAKEPUBLISHER_H


#include "CommsTypes.h"
#include "PublisherImpl.h"
#include "ThreadSafeQueue.h"

#include <memory>
#include <atomic>

class FakePubSubBackend;

class FakePublisher: public PublisherImpl {
public:
    FakePublisher(TopicIdentifier& topicId, FakePubSubBackend& provider);
    ~FakePublisher() override = default;

    Status Init() override;
    Status Push(std::string msg) override;
private:
    std::atomic_bool m_initialized = false;

    TopicIdentifier m_topicId;

    FakePubSubBackend& m_pubSubProvider;
};

#endif //COMMS_MIDDLEWARE_FAKEPUBLISHER_H
