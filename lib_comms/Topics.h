//
// Created by manojv on 2/25/23.
//

#ifndef COMMS_MIDDLEWARE_TOPICS_H
#define COMMS_MIDDLEWARE_TOPICS_H

#include <string>

namespace Topic {

    struct BasicTopic {
        using payloadType = std::string;

        static std::string GetName() {
            return "BasicTopic";
        }
    };
}


#endif //COMMS_MIDDLEWARE_TOPICS_H
