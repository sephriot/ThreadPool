//
// Created by wojtowic on 30.07.17.
//

#ifndef AUTONOMOUS_THREADPOOL_H
#define AUTONOMOUS_THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <thread>
#include <mutex>
#include <vector>

#include "Thread.h"


class ThreadPool {
public:
    ThreadPool(const ThreadPool&) = delete;
    ~ThreadPool();
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator = (const ThreadPool&) = delete;
    ThreadPool& operator = (ThreadPool&&) = delete;

    static ThreadPool& getInstance();
    void addJob(std::function<void()>);

private:
    ThreadPool();
    std::queue<std::function<void()>> m_queue;
    std::mutex m_queueMutex;
    std::condition_variable m_queueCondVar;
    std::vector<Thread> m_workers;
};


#endif //AUTONOMOUS_THREADPOOL_H
