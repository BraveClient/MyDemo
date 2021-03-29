/**
 * @file ringbuffer.h
 * @author yh (you@domain.com)
 * @brief 环型缓冲类
 * @version 0.1
 * @date 2021-03-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

namespace ringbuffer
{

    class RingBuffer
    {
    public:
        RingBuffer(unsigned num_items, size_t item_size);
        virtual ~RingBuffer();

        /**
         * @brief Put an item into the buffer.
         * 
         * @param val Item to put
         * @param val_size 
         * @return true if the item was put, false if 
         * @return false if the buffer is full
         */
        bool put(const void *val, size_t val_size = 0);
        bool put(int8_t val);
        bool put(uint8_t val);
        bool put(int16_t val);
        bool put(uint16_t val);
        bool put(int32_t val);
        bool put(uint32_t val);
        bool put(int64_t val);
        bool put(uint64_t val);
        bool put(float val);
        bool put(double val);

        /**
         * @brief 将项强制放入缓冲区，如果没有空间，则丢弃旧项。
         * 
         * @param val 
         * @param val_size 
         * @return true 有项被丢弃
         * @return false 
         */
        bool force(const void *val, size_t val_size = 0);
        bool force(int8_t val);
        bool force(uint8_t val);
        bool force(int16_t val);
        bool force(uint16_t val);
        bool force(int32_t val);
        bool force(uint32_t val);
        bool force(int64_t val);
        bool force(uint64_t val);
        bool force(float val);
        bool force(double val);

        /**
         * @brief Get an item from the buffer
         * 
         * @param val Item that was gotten
         * @param val_size Item size
         * @return true if an item was got
         * @return false if the buffer was empty
         */
         
        bool get(void *val, size_t val_size = 0);
        bool get(int8_t &val);
        bool get(uint8_t &val);
        bool get(int16_t &val);
        bool get(uint16_t &val);
        bool get(int32_t &val);
        bool get(uint32_t &val);
        bool get(int64_t &val);
        bool get(uint64_t &val);
        bool get(float &val);
        bool get(double &val);

        /**
         * @brief 获取缓冲区中可用数据项数量
         * 
         * @return unsigned 在缓冲区变满之前可以放入缓冲区的项数。
         */
        unsigned space(void);

        /**
         * @brief 获取缓冲区中已用用数据项数量
         * 
         * @return unsigned 
         */
        unsigned count(void);

        /**
         * @brief Returns true if the buffer is empty.
         * 
         * @return true 
         * @return false 
         */
        bool empty();

        /**
         * @brief Returns true if the buffer is full.
         * 
         * @return true 
         * @return false 
         */
        bool full();

        /**
         * @brief 返回缓冲区的容量，如果无法分配缓冲区，则返回0。
         * 
         * @return unsigned 
         */
        unsigned size();

        /**
         * @brief 清空缓冲区
         * 
         */
        void flush();
        void clear();

        /**
         * @brief resize the buffer.
         * 多线程不安全，需要加锁。
         * 
         * @param new_size 
         * @return true if the resize succeeds
         * @return false if not (allocation error)
         */
        bool resize(unsigned new_size);

        /**
         * @brief printf() some info on the buffer
         * 
         * @param name 
         */
        void print_info(const char *name);

    private:
        unsigned _num_items;//缓冲数据总数
        const size_t _item_size;//单个数据长度
        char *_buf; //缓冲buffer
        volatile unsigned _head; /* 指向插入节点指针 */
        volatile unsigned _tail; /* 指向删除节点指针 */

        unsigned _next(unsigned index);

        /* we don't want this class to be copied */
        RingBuffer(const RingBuffer &)=delete;
        RingBuffer operator=(const RingBuffer &)=delete;
    };

} // namespace ringbuffer
