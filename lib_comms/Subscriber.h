//
// Created by manojv on 2/22/23.
//

#ifndef COMMS_MIDDLEWARE_SUBSCRIBER_H
#define COMMS_MIDDLEWARE_SUBSCRIBER_H

#include <unordered_map>
#include <string>
#include <memory>
#include <optional>
#include <vector>

#include "CommsTypes.h"

class Subscriber {
public:
    virtual ~Subscriber() = default;

    virtual Status Init() = 0;
    virtual std::optional<Message> GetMessage() = 0;
};
using SubscriberPtr = std::unique_ptr<Subscriber>;

#endif //COMMS_MIDDLEWARE_SUBSCRIBER_H
