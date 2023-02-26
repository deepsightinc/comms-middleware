//
// Created by manojv on 2/22/23.
//

#ifndef COMMS_MIDDLEWARE_PUBLISHER_H
#define COMMS_MIDDLEWARE_PUBLISHER_H

#include <memory>

#include "CommsTypes.h"

class Publisher {
public:
    virtual ~Publisher() = default;

    virtual Status Init() = 0;
    virtual Status Push(std::string msg) = 0;
};
using PublisherPtr = std::unique_ptr<Publisher>;

#endif //COMMS_MIDDLEWARE_PUBLISHER_H
