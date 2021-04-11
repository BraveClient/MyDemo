/**
 * @file RWLockDataBase.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <pthread.h>
#include <time.h>
#include "../rwlock_writeFirst.hpp"

template <typename T>
class rwLockDataBase
{
private:
    struct timespec timeNow;
    T _data;
    rwlock_writeFirst _lk;

public:
    rwLockDataBase(){};
    ~rwLockDataBase() {}

    int writeData(const T &in)
    {
        unique_writeguard<rwlock_writeFirst> locker(_lk);
        _data = in;
        return 0;
    }
    int tryWriteData(const T &in, const int waitMilliseconds = 0)
    {
        if(-1 == _lk.tryLockWrite(waitMilliseconds))
        {
            
        }
    }
    int readData(T &out) {}
    int tryReadData(T &out, const int waitMilliseconds = 0) { return -1; }
    std::shared_ptr<T> readData() {}
    std::shared_ptr<T> tryReadData(const int waitMilliseconds = 0) {}
};

template <typename T>
class rwLockDataBase_posix
{
private:
    struct timespec timeNow;
    pthread_rwlock_t *_rwLock = nullptr;
    bool _init = false;
    T _data;

public:
    rwLockDataBase()
    {
        pthread_rwlock_init(_rwLock, NULL);
    };
    ~rwLockDataBase() {}
    int writeData(const T &in) {}
    int tryWriteData(const T &in, const int waitime = -1) int readData(T &out) {}
    int tryReadData(T &out) {}
    std::shared_ptr<T> readData() {}
    std::shared_ptr<T> tryReadData() {}
};
