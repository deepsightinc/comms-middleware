//
// Created by manojv on 2/22/23.
//
//#include "lib_comms/comms.h"
#include <thread>
#include <chrono>
#include <iostream>

#include <popl.h>

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
}
