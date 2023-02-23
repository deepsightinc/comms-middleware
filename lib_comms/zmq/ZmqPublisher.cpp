
#include <iostream>
#include "ZmqPublisher.h"
#include "zmq.hpp"

ZmqPublisher::ZmqPublisher(std::string ipAddress, int port) :
    m_context(std::make_unique<zmq::context_t>()),
    m_socket(std::make_unique<zmq::socket_t>(*m_context, zmq::socket_type::pub)),
    m_ip(ipAddress), m_port(port){}

ZmqPublisher::~ZmqPublisher() {}

Status ZmqPublisher::Init() {
    try {
        m_socket->bind("tcp://" + m_ip + ":" + std::to_string(m_port));
    }
    catch (const zmq::error_t& error) {
        std::cout << "error while initializing ZMQ publisher: " + std::string(error.what()) << std::endl;
        return Status::ERR;
    }
    return Status::OK;
}

Status ZmqPublisher::Push(std::string msg) {
    const auto result = m_socket->send(zmq::message_t(msg), zmq::send_flags::none);
    if(!result.has_value()) {
        std::cout << "Error: ZmqPublisher::Push() failed" << std::endl;
        return Status::ERR;
    }

    if(result.value() != msg.length()) {
        std::cout << "Error: failed to write expected number of bytes: " + std::to_string(msg.length())
                                                                        + " actual: "
                                                                        + std::to_string(result.value()) << std::endl;
        return Status::ERR;
    }
    return Status::OK;
}
