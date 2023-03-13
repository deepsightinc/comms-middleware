
#include <gtest/gtest.h>
#include "Comms.h"
#include <chrono>
#include "Topics.h"
#include <thread>
#include "FakePubSubBackend.h"

namespace {
    constexpr std::chrono::milliseconds k_receiveMessageTimeout = std::chrono::milliseconds{1000};


    template <typename SubscriberPtr>
    std::optional<std::string> waitForMessage(const SubscriberPtr& subscriber, std::chrono::milliseconds timeout) {
        auto start_time = std::chrono::high_resolution_clock::now();
        auto end_time = std::chrono::high_resolution_clock::now();

        while(end_time - start_time < timeout) {
            end_time = std::chrono::high_resolution_clock::now();

            auto maybeMessage = subscriber->GetMessage();
            if(!maybeMessage) {
                continue;
            }
            return maybeMessage.value();
        }
        return {};
    }

    template <typename SubscriberPtr>
    std::optional<std::string> waitForMessage(const SubscriberPtr& subscriber) {
        return waitForMessage(subscriber, k_receiveMessageTimeout);
    }
}

class PubSubTest: public ::testing::Test { 
public:
   PubSubTest()  = default;

   void SetUp() override {
       ASSERT_EQ (m_middleware.Init(), Status::OK);
   }

protected:
    Comms m_middleware;
};

TEST_F(PubSubTest, PublisherNoInit) {
    auto publisher = m_middleware.CreatePublisher<Topic::BasicTopic>( "*", 3000);
    ASSERT_EQ(publisher->Push("hello world"), Status::ERR);
}

TEST_F(PubSubTest, SubscriberNoInit) {
    auto publisher = m_middleware.CreatePublisher<Topic::BasicTopic>( "*", 3000);
    ASSERT_EQ(publisher->Init(), Status::OK);
    auto subscriber = m_middleware.CreateSubscriber<Topic::BasicTopic>( "localhost", 3000);

    ASSERT_EQ(publisher->Push("hello world"), Status::OK);

    ASSERT_FALSE(subscriber->GetMessage());
}


TEST_F(PubSubTest, SinglePublisherSingleSubscriber) {
    auto publisher = m_middleware.CreatePublisher<Topic::BasicTopic>( "*", 3000);

    ASSERT_EQ(publisher->Init(), Status::OK);

    auto subscriber = m_middleware.CreateSubscriber<Topic::BasicTopic>("localhost", 3000);
    ASSERT_EQ(subscriber->Init(), Status::OK);

    ASSERT_EQ(publisher->Push("hello world"), Status::OK);

    // TODO: Find better way of deterministically testing subscriber receive
    auto some_msg = waitForMessage(subscriber);
    ASSERT_TRUE(some_msg);
    ASSERT_EQ("hello world", some_msg.value());
}

TEST_F(PubSubTest, SinglePublisherMultipleSubscribers) {

    auto publisher = m_middleware.CreatePublisher<Topic::BasicTopic>( "*", 3000);
    ASSERT_EQ(publisher->Init(), Status::OK);

    auto subscriber = m_middleware.CreateSubscriber<Topic::BasicTopic>("localhost", 3000);
    ASSERT_EQ(subscriber->Init(), Status::OK);
    auto subscriber2 = m_middleware.CreateSubscriber<Topic::BasicTopic>("localhost", 3000);
    ASSERT_EQ(subscriber2->Init(), Status::OK);


    ASSERT_EQ(publisher->Push("hello world"), Status::OK);
    std::this_thread::sleep_for(std::chrono::milliseconds{30});

    auto some_msg = waitForMessage(subscriber);
    auto some_msg2 = waitForMessage(subscriber2);

    ASSERT_TRUE(some_msg);
    ASSERT_EQ("hello world", some_msg.value());

    ASSERT_TRUE(some_msg2);
    ASSERT_EQ("hello world", some_msg2.value());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}