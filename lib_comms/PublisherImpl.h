#ifndef COMMS_MIDDLEWARE_PUBLISHERIMPL_H
#define COMMS_MIDDLEWARE_PUBLISHERIMPL_H

#include <memory>

#include "CommsTypes.h"

class PublisherImpl {
public:
    virtual ~PublisherImpl() = default;

    virtual Status Init() = 0;
    virtual Status Push(std::string msgData) = 0;
};
using PublisherImplPtr = std::unique_ptr<PublisherImpl>;

#endif //COMMS_MIDDLEWARE_PUBLISHERIMPL_H
