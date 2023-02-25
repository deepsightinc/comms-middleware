
#include <iostream>
#include "ZmqSubscriber.h"

// modifications to support polling
#define ZMQ_BUILD_DRAFT_API 1
#define ZMQ_HAVE_POLLER 1
#include "zmq.hpp"

ZmqSubscriber::ZmqSubscriber(std::string ipAddress, int port, std::shared_ptr<zmq::context_t> context) :
    m_context(context),
    m_ip(ipAddress), m_port(port){}

ZmqSubscriber::~ZmqSubscriber() {
    m_cancelThread = true;
    m_subscriberThread.join();
}

Status ZmqSubscriber::Init() {

    m_subscriberThread = std::thread([this]{SubscriberLoop();});


    return Status::OK;
}

void ZmqSubscriber::SubscriberLoop() {
    zmq::socket_t socket(*m_context, zmq::socket_type::sub);
    try {
        socket.connect("tcp://" + m_ip + ":" + std::to_string(m_port));
        socket.set(zmq::sockopt::subscribe, "");
    }
    catch (const zmq::error_t& error) {
        std::cout << "Error: Could not initialize subscriber socket: " << error.what() << std::endl;
        return;
    }

    zmq::poller_t<> socketPoller;
    socketPoller.add(socket, zmq::event_flags::pollin);
    std::chrono::milliseconds pollTimeout{100};

    // can pre allocate size since we are only checking for 1 socket
    std::vector<decltype(socketPoller)::event_type> in_socket(1);

    while(!m_cancelThread) {
        const auto poll_res = socketPoller.wait_all(in_socket, pollTimeout);
        if(!poll_res) {
            continue;
        }

        zmq::message_t newMessage;
        auto socketMsg = in_socket[0].socket.recv(newMessage, zmq::recv_flags::none);
        if(!socketMsg.has_value()) {
            std::cout << "Error: Failed to unpack message from zmq::socket_t::recv" << std::endl;
            continue;
        }
        m_queue.push(newMessage.to_string());
    }
}

std::optional<std::string> ZmqSubscriber::GetMessage() {
    return m_queue.pop();
}
