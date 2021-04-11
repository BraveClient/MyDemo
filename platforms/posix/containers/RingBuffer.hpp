/**
 * @file RingBuffer.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

template <typename T, int N>
class RingBuf
{
public:
    RingBuf() : _capSize(N)
    {
        _first = 0;
        _last = 0;
        _size = 0;
    }
    ~RingBuf() {}

    T front() const
    {
        return _buf[_first];
    }

    bool pop(T &a)
    {
        if (isEmpty())
        {
            return false;
        }
        a = _buf[_first++];
        _first %= _capSize;
        _size -= 1;
        return true;
    }
    bool push(T a)
    {
        _buf[_last] = a;
        _last = (++_last) % _capSize;

        if (isFull())
        {
            _first = (++_first) % _capSize;
        }
        else
        {
            _size += 1;
        }
        return true;
    }
    bool tryPush(T a)
    {
        if (isFull())
        {
            return false;
        }
        _buf[_last] = a;
        _last = (++_last) % _capSize;
        _size += 1;
        return true;
    }

    inline bool isEmpty()
    {
        return _size == 0;
    }
    inline bool isFull()
    {
        return _size == _capSize;
    }
    inline void clear()
    {
        _first = 0;
        _last = 0;
        _size = 0;
    }

private:
    T _buf[N];
    int _first;
    int _last;
    int _size;
    const int _capSize;
};