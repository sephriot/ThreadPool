//
// Created by wojtowic on 30.07.17.
//

#ifndef AUTONOMOUS_THREAD_H
#define AUTONOMOUS_THREAD_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

class Thread {
public:
    Thread(std::queue<std::function<void()>>&, std::mutex&, std::condition_variable&);
    ~Thread();
    Thread(const Thread&) = delete;
    Thread(Thread&&) = default;
    Thread& operator = (const Thread&) = delete;
    Thread& operator = (Thread&&) = default;

    void finish();

private:
    void work();
    bool deleting = false;
    std::thread m_worker;
    std::queue<std::function<void()>>& m_queue;
    std::mutex& m_queueMutex;
    std::condition_variable& m_queueCondVar;
};


#endif //AUTONOMOUS_THREAD_H
