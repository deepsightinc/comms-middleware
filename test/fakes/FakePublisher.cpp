
#include "FakePublisher.h"
#include "FakePubSubBackend.h"
#include <iostream>

FakePublisher::FakePublisher(TopicIdentifier& topicId, FakePubSubBackend& pubSubProvider) : 
    m_topicId(topicId), m_pubSubProvider(pubSubProvider)
{}


Status FakePublisher::Init() {
    m_initialized = true;
    return Status::OK;
}

Status FakePublisher::Push(std::string msg) {
    if(!m_initialized) {
        std::cout << "Cannot push message before publisher is initialized" << std::endl;
        return Status::ERR;
    }
    
    m_pubSubProvider.PushMessageData(m_topicId, msg);
    return Status::OK;
}
