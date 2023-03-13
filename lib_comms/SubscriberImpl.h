#ifndef COMMS_MIDDLEWARE_SUBSCRIBERIMPL_H
#define COMMS_MIDDLEWARE_SUBSCRIBERIMPL_H

#include <string>
#include <memory>
#include <optional>

#include "CommsTypes.h"

class SubscriberImpl {
public:
    virtual ~SubscriberImpl() = default;

    virtual Status Init() = 0;
    virtual std::optional<Message> GetMessage() = 0;
};
using SubscriberImplPtr = std::unique_ptr<SubscriberImpl>;

#endif //COMMS_MIDDLEWARE_SUBSCRIBERIMPL_H
