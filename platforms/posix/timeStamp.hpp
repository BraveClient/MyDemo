/**
 * @file TimeStamp.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <ctime>
#include <unistd.h>
#include <stdint.h>

class TimeStamp
{
public:
    struct timespec timeNow;

    constexpr TimeStamp() : timeNow({0, 0}) {}
    constexpr TimeStamp(const timespec time) : timeNow(time) {}
    void operator()(const timespec time)
    {
        timeNow = time;
    }

    bool initTimenow()
    {
        return (0==clock_gettime(CLOCK_MONOTONIC,&timeNow));
    }

    uint32_t toSecond()
    {
        return timeNow.tv_sec;
    };
    uint64_t toMillisecond()
    {
        return timeNow.tv_sec * 1000 + timeNow.tv_nsec / 1000 / 1000;
    };
    uint64_t toMicrosecond()
    {
        return timeNow.tv_sec * 1000ll * 1000LL + timeNow.tv_nsec / 1000;
    }
    uint64_t toNanosecond()
    {
        return timeNow.tv_sec * 1000ll * 1000LL * 1000LL + timeNow.tv_nsec;
    }

    TimeStamp operator+(const TimeStamp &v) const
    {
        struct timespec time0;
        time0.tv_nsec = timeNow.tv_nsec + v.timeNow.tv_nsec;
        if (time0.tv_nsec >= 1000000000l)
        {
            time0.tv_sec = timeNow.tv_sec + v.timeNow.tv_sec + 1;
            time0.tv_nsec -= 1000000000l;
        }
        else
        {
            time0.tv_sec = timeNow.tv_sec + v.timeNow.tv_sec;
        }
        return TimeStamp(time0);
    }

    TimeStamp operator-(const TimeStamp &v) const
    {
        struct timespec time0;
        time0.tv_nsec = timeNow.tv_nsec - v.timeNow.tv_nsec;
        if (time0.tv_nsec < 0)
        {
            time0.tv_sec = timeNow.tv_sec - v.timeNow.tv_sec - 1;
            time0.tv_nsec += 1000000000l;
        }
        else
        {
            time0.tv_sec = timeNow.tv_sec - v.timeNow.tv_sec;
        }
        return TimeStamp(time0);
    }

    TimeStamp &operator+=(const TimeStamp &v)
    {
        timeNow.tv_nsec += v.timeNow.tv_nsec;
        if (timeNow.tv_nsec >= 1000000000l)
        {
            timeNow.tv_sec = timeNow.tv_sec + v.timeNow.tv_sec + 1;
            timeNow.tv_nsec -= 1000000000l;
        }
        else
        {
            timeNow.tv_sec += v.timeNow.tv_sec;
        }
        return *this;
    }

    TimeStamp &operator-=(const TimeStamp &v)
    {
        timeNow.tv_nsec -= v.timeNow.tv_nsec;
        if (timeNow.tv_nsec < 0l)
        {
            timeNow.tv_sec = timeNow.tv_sec - v.timeNow.tv_sec - 1;
            timeNow.tv_nsec -= 1000000000l;
        }
        else
        {
            timeNow.tv_sec -= v.timeNow.tv_sec;
        }
        return *this;
    }

    inline bool operator<(const TimeStamp &v)
    {
        if (this->timeNow.tv_sec < v.timeNow.tv_sec)
            return true;
        else if (this->timeNow.tv_sec == v.timeNow.tv_sec)
            return (this->timeNow.tv_nsec < v.timeNow.tv_nsec);
        else
            return false;
    }
    inline bool operator<=(const TimeStamp &v)
    {
        if (this->timeNow.tv_sec < v.timeNow.tv_sec)
            return true;
        else if (this->timeNow.tv_sec == v.timeNow.tv_sec)
            return (this->timeNow.tv_nsec <= v.timeNow.tv_nsec);
        else
            return false;
    }
    inline bool operator==(const TimeStamp &v)
    {
        if (this->timeNow.tv_sec != v.timeNow.tv_sec)
            return false;
        else if (this->timeNow.tv_sec == v.timeNow.tv_sec)
            return (this->timeNow.tv_nsec == v.timeNow.tv_nsec);
        else
            return false;
    }
    inline bool operator>=(const TimeStamp &v)
    {
        if (this->timeNow.tv_sec > v.timeNow.tv_sec)
            return true;
        else if (this->timeNow.tv_sec == v.timeNow.tv_sec)
            return (this->timeNow.tv_nsec >= v.timeNow.tv_nsec);
        else
            return false;
    }

    inline bool operator>(const TimeStamp &v)
    {
        if (this->timeNow.tv_sec > v.timeNow.tv_sec)
            return true;
        else if (this->timeNow.tv_sec == v.timeNow.tv_sec)
            return (this->timeNow.tv_nsec > v.timeNow.tv_nsec);
        else
            return false;
    }
};