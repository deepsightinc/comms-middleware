#ifndef COMMS_MIDDLEWARE_TYPES_H
#define COMMS_MIDDLEWARE_TYPES_H

#include <string>
#include <vector>

enum class Status {
    OK,
    ERR
};

using Message = std::string;
using Messages = std::vector<Message>;
using TopicName = std::string;
using IpAddress = std::string;
using Port = int;
using TopicIdentifier = std::tuple<TopicName, IpAddress, Port>;


#endif //COMMS_MIDDLEWARE_TYPES_H
