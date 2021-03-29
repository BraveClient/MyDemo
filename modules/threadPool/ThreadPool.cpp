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
        { //��ʼ���߳�����
            pool.emplace_back(
                [this] { // �����̺߳���
                    while (!this->stoped)
                    {
                        std::function<void()> task;
                        {                                                    // ��ȡһ����ִ�е� task
                            std::unique_lock<std::mutex> lock{this->m_lock}; // unique_lock ��� lock_guard �ĺô��ǣ�������ʱ unlock() �� lock()
                            this->cv_task.wait(lock,
                                               [this] {
                                                   return this->stoped.load() || !this->tasks.empty();
                                               }); // wait ֱ���� task
                            if (this->stoped && this->tasks.empty())
                                return;
                            task = std::move(this->tasks.front()); // ȡһ�� task
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
        cv_task.notify_all(); // ���������߳�ִ��
        for (std::thread &thread : pool)
        {
            //thread.detach(); // ���̡߳���������
            if (thread.joinable())
                thread.join(); // �ȴ���������� ǰ�᣺�߳�һ����ִ����
        }
}

