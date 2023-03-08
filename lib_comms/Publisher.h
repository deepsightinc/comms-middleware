//
// Created by manojv on 2/22/23.
//

#ifndef COMMS_MIDDLEWARE_PUBLISHER_H
#define COMMS_MIDDLEWARE_PUBLISHER_H

#include <memory>

#include "CommsTypes.h"
#include "PublisherImpl.h"

template<typename Payload>
class Publisher {
public:
    Publisher(PublisherImplPtr&& impl) : m_impl(std::move(impl)) {}

    Status Init() {
        return m_impl->Init();
    }
    Status Push(const Payload& msg) {
            // TODO: static assert on protobuf base type
            std::string serializedMessage = "";

            // quick conditional compilation here to avoid template specialization
            if constexpr(std::is_same<Payload, std::string>::value) {
                serializedMessage = msg;
            } else {
                serializedMessage = msg.ToString();
            }
            return m_impl->Push(msg);
    };
private:
    PublisherImplPtr m_impl;
};

template<typename Payload>
using PublisherPtr = std::unique_ptr<Publisher<Payload>>;

#endif //COMMS_MIDDLEWARE_PUBLISHER_H
