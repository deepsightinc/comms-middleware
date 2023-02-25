
#include <iostream>
#include "ZmqSubscriber.h"
#include "zmq.hpp"

ZmqSubscriber::ZmqSubscriber(std::string ipAddress, int port, std::shared_ptr<zmq::context_t> context) :
    m_context(context),
    m_socket(std::make_unique<zmq::socket_t>(*m_context, zmq::socket_type::sub)),
    m_ip(ipAddress), m_port(port){}

ZmqSubscriber::~ZmqSubscriber() {}

Status ZmqSubscriber::Init() {
    try {
        m_socket->connect("tcp://" + m_ip + ":" + std::to_string(m_port));
        m_socket->set(zmq::sockopt::subscribe, "");
    }
    catch (const zmq::error_t& error) {
        std::cout << error.what() << std::endl;
        return Status::ERR;
    }
    return Status::OK;
}

std::optional<Message> ZmqSubscriber::GetMessage() {
    zmq::message_t receivedMsg;
    const auto result = m_socket->recv(receivedMsg, zmq::recv_flags::none);
    if(!result.has_value()) {
        std::cout << "Error: ZmqSubscriber::GetMessage() failed" << std::endl;
        return {};
    }

    return {receivedMsg.to_string()};
}

std::optional<Messages> ZmqSubscriber::GetMessages() {
    // TODO: fill in logic
    return {};
}
