/**
 * @file ThreadsafeRingBuffer.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include "RingBuffer.hpp"
#include "AbstructThreadsafeMethod.hpp"

template <typename T, int N>
class ThreadsafeRingbuffer : public AbstructThreadsafeMethod<T>
{
private:
    mutable std::mutex _mutex; // 1 互斥量必须是可变的
    std::condition_variable _condition;
    RingBuf<T, N> _data_queue;
    int _maxQueueSize = N;

public:
    ThreadsafeRingbuffer()
    {
    }
    ThreadsafeRingbuffer(ThreadsafeRingbuffer const &other)
    {
        std::lock_guard<std::mutex> locker(other._mutex);
        _data_queue = other._data_queue;
    }

    bool isFull() override
    {
        return _data_queue.isFull();
    }
    bool isEmpty() override
    {
        return _data_queue.isEmpty();
    }
    void clear() override
    {
        std::lock_guard<std::mutex> locker(_mutex);
        _data_queue.clear();
    }
    bool waitPush(T new_value) override
    {
        int i = 0;
        bool ret = false;
        //1000*1000 us 内
        while (!ret)
        {
            ret = tryPush(new_value);
            if (ret || (i > 1000))
            {
                break;
            }
            i++;
        }
        return ret;
    }
    bool tryPush(T new_value) override
    {
        bool ret = false;
        std::lock_guard<std::mutex> locker(_mutex);
        ret = _data_queue.tryPush(new_value);
        if( true == ret)
        {
            _condition.notify_one();
        }
        return ret;
    }
    bool waitPop(T &value) override
    {
        bool ret = false;
        std::unique_lock<std::mutex> locker(_mutex);
        _condition.wait(locker, [this] { return !_data_queue.isEmpty(); });
        ret = _data_queue.pop(value);
        return ret;
    }
    std::shared_ptr<T> waitPop() override
    {
        // TODO:
        return nullptr;
    }
    bool tryPop(T &value) override
    {
        bool ret = false;
        std::lock_guard<std::mutex> locker(_mutex);
        ret = _data_queue.pop(value);
        return ret;
    }
    std::shared_ptr<T> tryPop() override
    {
        // TODO
        return nullptr;
    }
};