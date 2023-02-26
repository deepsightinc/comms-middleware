//
// Created by manojv on 2/22/23.
//
//#include "lib_comms/comms.h"
#include <thread>
#include <chrono>
#include <iostream>

#include <popl.h>
#include "Comms.h"

int main(int argc, char** argv) {
    popl::OptionParser op("Test server that emits random messages to client.\nAllowed options");
    auto help_option   = op.add<popl::Switch>("h", "help", "produce help message");
    auto ip_option = op.add<popl::Implicit<std::string>>("i", "ip_address", "ip used to bind to clients", "*");
    auto port_option  = op.add<popl::Implicit<int>>("p", "port", "port used to bind to clients", 3000 );
    op.parse(argc, argv);

    // print auto-generated help message
    if (help_option->is_set()) {
        std::cout << op << std::endl;
        return 0;
    }

    Comms middleware({});
    PublisherPtr publisher = middleware.CreatePublisher("test_topic", ip_option->value(), port_option->value());

    std::cout << "starting server with IP address: " << ip_option->value() << " port: " << port_option->value() << std::endl;

    if(publisher->Init() != Status::OK) {
        std::cout << "Publisher failed to initialize" << std::endl;
        return 0;
    }

    unsigned messageId = 0;
    while(true) {
        std::cout << "Writing messageId: " << std::to_string(messageId) << std::endl;
        publisher->Push("message id: " + std::to_string(messageId));
        std::this_thread::sleep_for(std::chrono::milliseconds{100});
        messageId++;
    }
}
