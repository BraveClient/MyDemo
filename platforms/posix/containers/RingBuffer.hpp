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
class RingBuffer
{
public:
    RingBuffer() : _capSize(N)
    {
        _first = 0;
        _last = 0;
        _size = 0;
    }
    ~RingBuffer() {}

    T front() const
    {
        return _buf[_first];
    }
    T back() const
    {
        int count = (_last == 0) ? (_capSize - 1) : (_last - 1);
        return _buf[count];
    }

    bool pop(T &a)
    {
        if (empty())
        {
            return false;
        }
        a = _buf[_first++];
        _first %= _capSize;
        _size -= 1;
        return true;
    }
    bool pop()
    {
        if (empty())
        {
            return false;
        }
        _first++;
        _first %= _capSize;
        _size -= 1;
        return true;
    }

    /**
     * @brief 将项强制放入缓冲区，如果没有空间，则丢弃旧项。
     * 
     * @param a 
     * @return true 有项被丢丢弃
     * @return false 
     */
    bool push_force(T a)
    {
        _buf[_last] = a;
        _last = (++_last) % _capSize;

        if (full())
        {
            _first = (++_first) % _capSize;
            return true;
        }
        else
        {
            _size += 1;
            return false;
        }
    }

    /**
     * @brief 将项放入缓冲区
     * 
     * @param a 
     * @return true 有空间，成功
     * @return false 无空间，失败
     */
    bool push(T a)
    {
        if (full())
        {
            return false;
        }
        _buf[_last] = a;
        _last = (++_last) % _capSize;
        _size += 1;
        return true;
    }

    inline bool empty() { return _size == 0; }
    inline bool full() { return _size == _capSize; }
    inline void clear()
    {
        _first = 0;
        _last = 0;
        _size = 0;
    }
    inline int count() { return _size; }
    inline int space() { return _capSize - _size; }
    inline int size() { return _capSize; }

private:
    T _buf[N];
    int _first;
    int _last;
    int _size;
    const int _capSize;
    RingBuffer(const RingBuffer &) = delete;
    RingBuffer operator=(const RingBuffer &) = delete;
};