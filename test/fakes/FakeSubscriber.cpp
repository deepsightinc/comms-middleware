
#include <iostream>
#include "FakeSubscriber.h"
#include "FakePubSubBackend.h"


FakeSubscriber::FakeSubscriber(TopicIdentifier topicId,  
FakePubSubBackend& provider) :
    m_topicId(topicId),
    m_provider(provider) {
        m_provider.RegisterSubscriber(m_topicId, this);
    }

FakeSubscriber::~FakeSubscriber() {
    m_provider.UnregisterSubscriber(m_topicId, this);
}

Status FakeSubscriber::Init() {
    if (m_initialized) {
        return Status::OK;
    }

    m_initialized = true;
    return Status::OK;
}

std::optional<std::string> FakeSubscriber::GetMessage() {
    if (!m_initialized) {
        std::cout << "Error: Cannot get message from subscriber, subscriber not initialized" << std::endl;
        return {};
    }

    return m_queue.pop();
}
