
#include <gtest/gtest.h>
#include "Comms.h"
#include <chrono>
#include <thread>

std::optional<std::string> waitForMessage(const SubscriberPtr& subscriber, std::chrono::milliseconds timeout) {
    auto start_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();

    while(end_time - start_time < timeout) {
        auto maybeMessage = subscriber->GetMessage();
        if(!maybeMessage) {
            continue;
        }
        return maybeMessage.value();
    }
    return {};
}

TEST(PubSubTest, InitialTest) {
    Comms middleware({});
    middleware.Init();
    auto publisher = middleware.CreatePublisher("topic", "*", 3000);
    ASSERT_TRUE(publisher->Init() == Status::OK);

    auto subscriber = middleware.CreateSubscriber("topic","localhost", 3000);
    ASSERT_TRUE(subscriber->Init() == Status::OK);

    std::this_thread::sleep_for(std::chrono::milliseconds{30});

    ASSERT_TRUE(publisher->Push("hello world") == Status::OK);
    ASSERT_TRUE(publisher->Push("hello darling") == Status::OK);

    // TODO: Find better way of deterministically testing subscriber receive
    auto some_msg = waitForMessage(subscriber, std::chrono::milliseconds {100});

    ASSERT_TRUE(some_msg);
    ASSERT_EQ("hello world", some_msg.value());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}