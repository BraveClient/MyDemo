/**
 * @file ThreadPool.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ThreadPool.hpp"

ThreadPool::ThreadPool(unsigned short size)
{
            idlThrNum = size < 1 ? 1 : size;
        for (size = 0; size < idlThrNum; ++size)
        { //初始化线程数量
            pool.emplace_back(
                [this] { // 工作线程函数
                    while (!this->stoped)
                    {
                        std::function<void()> task;
                        {                                                    // 获取一个待执行的 task
                            std::unique_lock<std::mutex> lock{this->m_lock}; // unique_lock 相比 lock_guard 的好处是：可以随时 unlock() 和 lock()
                            this->cv_task.wait(lock,
                                               [this] {
                                                   return this->stoped.load() || !this->tasks.empty();
                                               }); // wait 直到有 task
                            if (this->stoped && this->tasks.empty())
                                return;
                            task = std::move(this->tasks.front()); // 取一个 task
                            this->tasks.pop();
                        }
                        idlThrNum--;
                        task();
                        idlThrNum++;
                    }
                });
        }
}

ThreadPool::~ThreadPool()
{
        stoped.store(true);
        cv_task.notify_all(); // 唤醒所有线程执行
        for (std::thread &thread : pool)
        {
            //thread.detach(); // 让线程“自生自灭”
            if (thread.joinable())
                thread.join(); // 等待任务结束， 前提：线程一定会执行完
        }
}

