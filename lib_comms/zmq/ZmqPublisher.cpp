
#include <iostream>
#include "ZmqPublisher.h"
#include "zmq.hpp"

ZmqPublisher::ZmqPublisher(std::string ipAddress, int port, std::shared_ptr<zmq::context_t> context) :
    m_context(context),
    m_socket(std::make_unique<zmq::socket_t>(*m_context, zmq::socket_type::pub)),
    m_ip(ipAddress), m_port(port){}

ZmqPublisher::~ZmqPublisher() {
    m_cancelThread = true;
    m_publisherThread.join();
}

Status ZmqPublisher::Init() {
    m_publisherThread = std::thread([this]{PublisherLoop();});
    m_initialized = true;
    return Status::OK;
}

void ZmqPublisher::PublisherLoop() {
    try {
        m_socket->bind("tcp://" + m_ip + ":" + std::to_string(m_port));
    }
    catch (const zmq::error_t& error) {
        std::cout << "error while initializing ZMQ publisher: " + std::string(error.what()) << std::endl;
        return;
    }

    while(!m_cancelThread) {
        auto maybeMsg = m_queue.pop();
        if(!maybeMsg) {
            // TODO: add a blocking call to pull data from queue to avoid repeated thread wakeups
            std::this_thread::sleep_for(std::chrono::milliseconds{100});
            continue;
        }

        const auto result = m_socket->send(zmq::message_t(maybeMsg.value()), zmq::send_flags::none);
        if (!result.has_value()) {
            std::cout << "Error: Unable to send message from zmq publisher" << std::endl;
            continue;
        }

        if (result.value() != maybeMsg.value().length()) {
            std::cout << "Error: failed to write expected number of bytes: " + std::to_string(maybeMsg.value().length())
                         + " actual: "
                         + std::to_string(result.value()) << std::endl;
            continue;
        }
    }
}


Status ZmqPublisher::Push(std::string msg) {
    if(!m_initialized) {
        std::cout << "Error: Cannot push message to publisher, subscriber not initialized" << std::endl;
        return Status::ERR;
    }
    m_queue.push(msg);
    return Status::OK;
}
