
#include <iostream>
#include "ZmqPublisher.h"
#include "zmq.hpp"

namespace {
    // calls to socket_t::bind() seem to be non-blocking, and messages can be lost if they are sent on a socket that is
    // still binding. This classes utilizes the monitor facilities in zmq to enable waiting to send queued up messages
    // until the socket is properly setup.
    class BindMonitor : public zmq::monitor_t {
    public:
        BindMonitor(std::atomic_bool& initFlag, std::condition_variable& condVar) :
        m_cv(condVar), m_initFlag(initFlag) {}

        void on_event_listening(const zmq_event_t& event,
                                const char* addr) override
        {
            m_initFlag.store(true);
            m_cv.notify_all();
        }
    private:
        std::condition_variable& m_cv;
        std::atomic_bool& m_initFlag;
    };

    constexpr std::chrono::milliseconds k_initializeTimeout = std::chrono::milliseconds{1000};
}

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

    std::unique_lock<std::mutex> lg(m_initializeMutex);
    bool successfulInit = m_initializeCv.wait_for(lg, k_initializeTimeout, [this]{
        std::cout << "testing" << std::endl;
        return m_initialized.load();
    });

    return successfulInit ? Status::OK : Status::ERR;
}

void ZmqPublisher::PublisherLoop() {
    try {
        BindMonitor bindMon(m_initialized, m_initializeCv);

        bindMon.init(*m_socket, "inproc://conmon", ZMQ_EVENT_LISTENING),
        m_socket->bind("tcp://" + m_ip + ":" + std::to_string(m_port));

        // Even after waiting for a successful bind, the first message will very rarely disappear. This wait ensures that
        // all messages are properly queued up.
        std::this_thread::sleep_for(std::chrono::milliseconds{300});
        bindMon.check_event(100);
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
