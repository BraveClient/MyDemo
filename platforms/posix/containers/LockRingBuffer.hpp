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
#include "LockArraryInterface.hpp"

template <typename T, int N>
class ThreadsafeRingbuffer : public LockArraryInterface<T, N>
{
private:
    RingBuf<T, N> _data_queue;

public:
    ThreadsafeRingbuffer()
    {
    }
    ThreadsafeRingbuffer(ThreadsafeRingbuffer const &other)
    {
        std::lock_guard<std::mutex> locker(other._mutex);
        _data_queue = other._data_queue;
    }

    bool resize(int size) override
    {
        //FIXME 自己写的ringbuff不支持resize
        return false;
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
        std::lock_guard<std::mutex> locker(this->_mutex);
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
        std::lock_guard<std::mutex> locker(this->_mutex);
        ret = _data_queue.tryPush(new_value);
        if (true == ret)
        {
            this->_condition.notify_one();
        }
        return ret;
    }
    bool waitPop(T &value) override
    {
        bool ret = false;
        std::unique_lock<std::mutex> locker(this->_mutex);
        this->_condition.wait(locker, [this] { return !_data_queue.isEmpty(); });
        ret = _data_queue.pop(value);
        return ret;
    }
    std::shared_ptr<T> waitPop() override
    {
        std::unique_lock<std::mutex> locker(this->_mutex);
        this->_condition.wait(locker, [this] { return !_data_queue.isEmpty(); });
        T temp;
        std::shared_ptr<T> res(std::make_shared<T>(_data_queue.front()));
        _data_queue.pop(temp);
        return res;
    }
    bool tryPop(T &value) override
    {
        bool ret = false;
        std::lock_guard<std::mutex> locker(this->_mutex);
        ret = _data_queue.pop(value);
        return ret;
    }
    std::shared_ptr<T> tryPop() override
    {
        std::lock_guard<std::mutex> locker(this->_mutex);
        if (_data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(_data_queue.front()));
        _data_queue.pop();
        return res;
    }
};