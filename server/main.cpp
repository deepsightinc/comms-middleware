//
// Created by manojv on 2/22/23.
//
//#include "lib_comms/comms.h"
#include <thread>
#include <chrono>
#include <iostream>

#include <popl.h>

int main(int argc, char** argv) {
    popl::OptionParser op("Test client that connects to server.\nAllowed options");
    auto help_option   = op.add<popl::Switch>("h", "help", "produce help message");
    auto ip_option = op.add<popl::Value<std::string>>("i", "ip_address", "ip of server to connect to");
    auto port_option  = op.add<popl::Value<int>>("p", "port", "port of server to connect to" );
    op.parse(argc, argv);

    // print auto-generated help message
    if (help_option->is_set())
        std::cout << op << std::endl;

    if(!ip_option->is_set() || !port_option->is_set() ) {
        std::cout << "Error: Missing required arguments" << std::endl;
        std::exit(0);
    }
}
