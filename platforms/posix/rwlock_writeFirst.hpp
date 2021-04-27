/**
 * @file rwlock_writeFirst.hpp
 * @author your name (you@domain.com)
 * @brief 写优先的读写锁
 * @version 0.1
 * @date 2021-04-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <stddef.h>

class rwlock_writeFirst
{
private:
    volatile size_t read_cnt{0};
    volatile size_t write_cnt{0};
    volatile bool inwriteflag{false};
    std::mutex counter_mutex;
    std::condition_variable cond_w;
    std::condition_variable cond_r;

public:
    rwlock_writeFirst() = default;
    ~rwlock_writeFirst() = default;

    int lockRead()
    {
        std::unique_lock<std::mutex> ulk(counter_mutex);
        cond_r.wait(ulk, [=]() -> bool { return write_cnt == 0; });
        ++read_cnt;
        return 0;
    }
    int lockWrite()
    {
        std::unique_lock<std::mutex> ulk(counter_mutex);
        ++write_cnt;
        cond_w.wait(ulk, [=]() -> bool { return read_cnt == 0 && !inwriteflag; });
        inwriteflag = true;
        return 0;
    }
    int unlockRead()
    {
        std::unique_lock<std::mutex> ulk(counter_mutex);
        if (--read_cnt == 0 && write_cnt > 0)
        {
            cond_w.notify_one();
        }
        return 0;
    }
    int unlockWrite()
    {
        std::unique_lock<std::mutex> ulk(counter_mutex);
        if (--write_cnt == 0)
        {
            cond_r.notify_all();
        }
        else
        {
            cond_w.notify_one();
        }
        inwriteflag = false;
        return 0;
    }
    int tryLockRead(int waitMilliseconds = 0)
    {
        std::unique_lock<std::mutex> ulk(counter_mutex);
        if (false == cond_r.wait_for(ulk,
                                     std::chrono::milliseconds(waitMilliseconds),
                                     [=]() -> bool { return write_cnt == 0; }))
        {
            return -1;
        }
        else
        {
            ++read_cnt;
            return 0;
        }
    }
    int tryLockWrite(int waitMilliseconds = 0)
    {
        std::unique_lock<std::mutex> ulk(counter_mutex);
        ++write_cnt;
        if (false == cond_w.wait_for(ulk,
                                     std::chrono::milliseconds(waitMilliseconds),
                                     [=]() -> bool { return read_cnt == 0 && !inwriteflag; }))
        {
            --write_cnt;
            return -1;
        }
        else
        {
            inwriteflag = true;
            return 0;
        }
    }
};

template <typename _RWLockable>
class unique_writeguard
{
public:
    explicit unique_writeguard(_RWLockable &rw_lockable)
        : rw_lockable_(rw_lockable)
    {
        rw_lockable_.lock_write();
    }
    ~unique_writeguard()
    {
        rw_lockable_.release_write();
    }

private:
    unique_writeguard() = delete;
    unique_writeguard(const unique_writeguard &) = delete;
    unique_writeguard &operator=(const unique_writeguard &) = delete;

private:
    _RWLockable &rw_lockable_;
};

template <typename _RWLockable>
class unique_readguard
{
public:
    explicit unique_readguard(_RWLockable &rw_lockable)
        : rw_lockable_(rw_lockable)
    {
        rw_lockable_.lock_read();
    }
    ~unique_readguard()
    {
        rw_lockable_.release_read();
    }

private:
    unique_readguard() = delete;
    unique_readguard(const unique_readguard &) = delete;
    unique_readguard &operator=(const unique_readguard &) = delete;

private:
    _RWLockable &rw_lockable_;
};
