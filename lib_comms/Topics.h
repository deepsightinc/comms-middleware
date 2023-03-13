#ifndef COMMS_MIDDLEWARE_TOPICS_H
#define COMMS_MIDDLEWARE_TOPICS_H

#include <string>

namespace Topic {

    // Topic structures encapsulate a payload type and a topic name. This payload type is used to 
    // enforce compile-time constraints on publishers/subscribers, and the topic name is used by subscribers
    // to filter relevant messages.
    // TODO: Investigate more aggressive use of static_asserts to provide more relevant error messages to devs
    struct BasicTopic {
        using payloadType = std::string;

        static std::string GetName() {
            return "BasicTopic";
        }
    };
}


#endif //COMMS_MIDDLEWARE_TOPICS_H
