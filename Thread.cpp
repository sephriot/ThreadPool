//
// Created by wojtowic on 30.07.17.
//

#include "Thread.h"

Thread::Thread(std::queue<std::function<void()>>& queue, std::mutex& queueMutex, std::condition_variable& queueCondVar)
:
    m_queue(queue),
    m_queueMutex(queueMutex),
    m_queueCondVar(queueCondVar)
{
    m_worker = std::thread(&Thread::work, this);
}

Thread::~Thread() {
    deleting = true;
    m_worker.join();
}

void Thread::work() {

    while(true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_queueCondVar.wait(lock, [&]{ return !m_queue.empty() || deleting; });
            if(deleting) {
                break;
            }
            job = m_queue.front();
            m_queue.pop();
        }
        job();
    }
}

void Thread::finish() {
    deleting = true;
}
