#ifndef COMMS_MIDDLEWARE_THREADSAFEQUEUE_H
#define COMMS_MIDDLEWARE_THREADSAFEQUEUE_H

#include <mutex>
#include <queue>
#include <condition_variable>
#include <optional>

template <typename T>
class ThreadSafeQueue {
public:
    void push(T item) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(item);
        m_cv.notify_one();
    }

    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(m_mutex);

        if(m_queue.empty()) {
            return {};
        }

        T item = m_queue.front();
        m_queue.pop();
        return item;
    }
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};

#endif //COMMS_MIDDLEWARE_THREADSAFEQUEUE_H
