/**
 * @file LockArraryInterface.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <condition_variable>
#include <memory>
#include <mutex>

template <typename T, int N>
class LockArraryInterface
{
public:
    LockArraryInterface() {}
    virtual ~LockArraryInterface() = default;

    virtual bool isFull() = 0;
    virtual bool isEmpty() = 0;
    virtual void clear() = 0;
    virtual bool waitPush(T new_value) = 0;
    virtual bool tryPush(T new_value) = 0;
    virtual bool waitPop(T &value) = 0;
    virtual std::shared_ptr<T> waitPop() = 0;
    virtual bool tryPop(T &value) = 0;
    virtual std::shared_ptr<T> tryPop() = 0;

protected:
    int _maxSize = N;                   //队列长度
    mutable std::mutex _mutex;          //  互斥量
    std::condition_variable _condition; //条件变量
};