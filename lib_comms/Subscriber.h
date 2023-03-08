//
// Created by manojv on 2/22/23.
//

#ifndef COMMS_MIDDLEWARE_SUBSCRIBER_H
#define COMMS_MIDDLEWARE_SUBSCRIBER_H

#include <string>
#include <memory>
#include <optional>

#include "SubscriberImpl.h"

#include "CommsTypes.h"

template<typename Payload>
class Subscriber {
public:
    Subscriber(SubscriberImplPtr&& impl) : m_impl(std::move(impl)) {}

    Status Init() {
        return m_impl->Init();
    }

    std::optional<Payload> GetMessage() {
        auto maybeMessage = m_impl->GetMessage();
        if(!maybeMessage) {
            return maybeMessage;
        }

        Payload message;
        if constexpr(std::is_same<Payload, std::string>::value) {
            message = maybeMessage.value();
        } else {
            const auto parsedCorrectly = message.ParseFromString(maybeMessage.value());
            if(!parsedCorrectly) {
                return {};
            }
        }
        return message;
    }

private:
    SubscriberImplPtr m_impl;
};

template<typename Payload>
using SubscriberPtr = std::unique_ptr<Subscriber<Payload>>;

#endif //COMMS_MIDDLEWARE_SUBSCRIBER_H
