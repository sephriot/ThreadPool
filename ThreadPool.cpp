//
// Created by wojtowic on 30.07.17.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
    m_workers.reserve(std::thread::hardware_concurrency());
    for(unsigned int i = 0; i < std::thread::hardware_concurrency(); ++i) {
        m_workers.emplace_back(m_queue, m_queueMutex, m_queueCondVar);
    }
}

void ThreadPool::addJob(std::function<void()> func) {

    std::lock_guard<std::mutex> lock(m_queueMutex);
    m_queue.push(func);
    m_queueCondVar.notify_one();
}

ThreadPool& ThreadPool::getInstance() {
    static ThreadPool pool;

    return pool;
}

ThreadPool::~ThreadPool() {
    for(auto& t : m_workers) {
        t.finish();
    }
    m_queueCondVar.notify_all();
}
