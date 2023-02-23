
#include <gtest/gtest.h>
#include "Comms.h"
#include <chrono>
#include <thread>

TEST(PubSubTest, InitialTest) {
    Comms middleware({});
    middleware.Init();
    auto publisher = middleware.CreatePublisher("topic", "*", 3000);
    ASSERT_TRUE(publisher->Init() == Status::OK);

    auto subscriber = middleware.CreateSubscriber("topic","localhost", 3000);
    ASSERT_TRUE(subscriber->Init() == Status::OK);

    std::this_thread::sleep_for(std::chrono::milliseconds{30});

    ASSERT_TRUE(publisher->Push("hello world") == Status::OK);
    auto some_msg = subscriber->GetMessage();
    ASSERT_TRUE(some_msg);
    ASSERT_EQ("hello world", some_msg.value());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}