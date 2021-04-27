/**
 * @file timeStamp.hpp
 * @author yh (you@domain.com)
 * @brief 时间类
 * @version 1.0
 * @date 2021-04-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_

#include <ctime>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

class TimeStamp
{
public:
    struct timespec stTime;
    struct tm *_tm = nullptr;

    constexpr TimeStamp() : stTime({0, 0}) {}
    constexpr TimeStamp(const timespec time) : stTime(time) {}
    constexpr TimeStamp(int second, int nanosecode = 0) : stTime({second, nanosecode}) {}
    TimeStamp(struct tm *time) { stTime.tv_sec = mktime(time); }
    void operator()(const timespec time)
    {
        stTime = time;
    }

    bool initTimenow(int type = CLOCK_MONOTONIC)
    {
        if (CLOCK_REALTIME == type)
        {
            return (0 == clock_gettime(CLOCK_REALTIME, &stTime));
        }
        else if (CLOCK_MONOTONIC == type)
        {
            _tm = localtime(&stTime.tv_sec);
            return (0 == clock_gettime(CLOCK_MONOTONIC, &stTime));
        }
        else
        {
            return false;
        }
    }
    static TimeStamp now(int type = CLOCK_MONOTONIC)
    {
        TimeStamp timenow;
        timenow.initTimenow(type);
        return timenow;
    }

    uint32_t year()
    {
        if (nullptr == _tm)
        {
            _tm = localtime(&stTime.tv_sec);
        }
        return _tm->tm_year + 1900;
    }
    uint32_t month()
    {
        if (nullptr == _tm)
        {
            _tm = localtime(&stTime.tv_sec);
        }
        return _tm->tm_mon + 1;
    }
    uint32_t day()
    {
        if (nullptr == _tm)
        {
            _tm = localtime(&stTime.tv_sec);
        }
        return _tm->tm_mday + 1970;
    }
    uint32_t hour()
    {
        if (nullptr == _tm)
        {
            _tm = localtime(&stTime.tv_sec);
        }
        return _tm->tm_hour;
    }
    uint32_t minute()
    {
        if (nullptr == _tm)
        {
            _tm = localtime(&stTime.tv_sec);
        }
        return _tm->tm_min;
    }
    uint32_t second()
    {
        if (nullptr == _tm)
        {
            _tm = localtime(&stTime.tv_sec);
        }
        return _tm->tm_sec;
    }

    /**
     * @brief 获取从初化后到现在的时间
     */
    TimeStamp lastTime()
    {
        TimeStamp timeNow = TimeStamp::now();
        return timeNow - *this;
    }

    uint32_t toSecond()
    {
        return stTime.tv_sec;
    };
    float toSecond_f()
    {
        return stTime.tv_sec + (float)stTime.tv_nsec / (1000.0 * 1000.0 * 1000.0);
    }
    uint64_t toMillisecond()
    {
        return stTime.tv_sec * 1000ll + stTime.tv_nsec / 1000ll / 1000ll;
    };
    uint64_t toMicrosecond()
    {
        return stTime.tv_sec * 1000ll * 1000LL + stTime.tv_nsec / 1000ll;
    }
    uint64_t toNanosecond()
    {
        return stTime.tv_sec * 1000ll * 1000LL * 1000LL + stTime.tv_nsec;
    }

    TimeStamp operator+(const TimeStamp &v) const
    {
        struct timespec time0;
        time0.tv_nsec = stTime.tv_nsec + v.stTime.tv_nsec;
        if (time0.tv_nsec >= 1000000000l)
        {
            time0.tv_sec = stTime.tv_sec + v.stTime.tv_sec + 1;
            time0.tv_nsec -= 1000000000l;
        }
        else
        {
            time0.tv_sec = stTime.tv_sec + v.stTime.tv_sec;
        }
        return TimeStamp(time0);
    }
    TimeStamp operator-(const TimeStamp &v) const
    {
        struct timespec time0;

        time0.tv_nsec = stTime.tv_nsec - v.stTime.tv_nsec;
        if (time0.tv_nsec < 0)
        {
            time0.tv_sec = stTime.tv_sec - v.stTime.tv_sec - 1;
            time0.tv_nsec += 1000000000l;
        }
        else
        {
            time0.tv_sec = stTime.tv_sec - v.stTime.tv_sec;
        }
        return TimeStamp(time0);
    }
    TimeStamp &operator+=(const TimeStamp &v)
    {
        stTime.tv_nsec += v.stTime.tv_nsec;
        if (stTime.tv_nsec >= 1000000000l)
        {
            stTime.tv_sec = stTime.tv_sec + v.stTime.tv_sec + 1;
            stTime.tv_nsec -= 1000000000l;
        }
        else
        {
            stTime.tv_sec += v.stTime.tv_sec;
        }
        return *this;
    }
    TimeStamp &operator-=(const TimeStamp &v)
    {
        stTime.tv_nsec -= v.stTime.tv_nsec;
        if (stTime.tv_nsec < 0l)
        {
            stTime.tv_sec = stTime.tv_sec - v.stTime.tv_sec - 1;
            stTime.tv_nsec -= 1000000000l;
        }
        else
        {
            stTime.tv_sec -= v.stTime.tv_sec;
        }
        return *this;
    }

    inline bool operator<(const TimeStamp &v)
    {
        if (this->stTime.tv_sec < v.stTime.tv_sec)
            return true;
        else if (this->stTime.tv_sec == v.stTime.tv_sec)
            return (this->stTime.tv_nsec < v.stTime.tv_nsec);
        else
            return false;
    }
    inline bool operator<=(const TimeStamp &v)
    {
        if (this->stTime.tv_sec < v.stTime.tv_sec)
            return true;
        else if (this->stTime.tv_sec == v.stTime.tv_sec)
            return (this->stTime.tv_nsec <= v.stTime.tv_nsec);
        else
            return false;
    }
    inline bool operator==(const TimeStamp &v)
    {
        if (this->stTime.tv_sec != v.stTime.tv_sec)
            return false;
        else if (this->stTime.tv_sec == v.stTime.tv_sec)
            return (this->stTime.tv_nsec == v.stTime.tv_nsec);
        else
            return false;
    }
    inline bool operator>=(const TimeStamp &v)
    {
        if (this->stTime.tv_sec > v.stTime.tv_sec)
            return true;
        else if (this->stTime.tv_sec == v.stTime.tv_sec)
            return (this->stTime.tv_nsec >= v.stTime.tv_nsec);
        else
            return false;
    }
    inline bool operator>(const TimeStamp &v)
    {
        if (this->stTime.tv_sec > v.stTime.tv_sec)
            return true;
        else if (this->stTime.tv_sec == v.stTime.tv_sec)
            return (this->stTime.tv_nsec > v.stTime.tv_nsec);
        else
            return false;
    }
    inline TimeStamp form(const TimeStamp &v)
    {
        TimeStamp now;
        now.initTimenow();
        return now - v;
    }
};

#endif // _TIMESTAMP_H_
