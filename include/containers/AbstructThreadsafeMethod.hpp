/**
 * @file AbstructThreadsafeMethod.hpp
 * @author yh(forgetsky001@qq.com)
 * @brief 线程安全的通信接口
 * @version 0.1
 * @date 2020-12-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once
#include <memory>

template <typename T>
class AbstructThreadsafeMethod
{
public:
    AbstructThreadsafeMethod(){_maxSize = 0;}
    virtual ~AbstructThreadsafeMethod() = default;

    virtual bool isFull() = 0;
    virtual bool isEmpty() = 0;
    virtual void clear() = 0;
    virtual bool waitPush(T new_value) = 0;
    virtual bool tryPush(T new_value) = 0;
    virtual bool waitPop(T &value) = 0;
    virtual std::shared_ptr<T> waitPop() = 0;
    virtual bool tryPop(T &value) = 0;
    virtual std::shared_ptr<T> tryPop() = 0;

private:
    int _maxSize;
};