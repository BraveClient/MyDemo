/**
 * @file ThreadsafeQueue.hpp
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
#include <queue>
#include "AbstructThreadsafeMethod.hpp"

template <typename T, int N>
class ThreadsafeQueue : public AbstructThreadsafeMethod<T>
{
private:
  mutable std::mutex _mutex; // 1 互斥量必须是可变的
  std::condition_variable _condition;
  std::queue<T> _data_queue;
  int _maxQueueSize = N;

public:
  ThreadsafeQueue()
  {
  }
  ThreadsafeQueue(ThreadsafeQueue const &other)
  {
    std::lock_guard<std::mutex> locker(other._mutex);
    _data_queue = other._data_queue;
  }

  bool isFull() override
  {
    return (_data_queue.size() >= _maxQueueSize);
  }
  bool isEmpty() override
  {
    return (_data_queue.empty());
  }
  void clear() override
  {
    std::lock_guard<std::mutex> locker(_mutex);
    std::queue<T> empty;
    std::swap(empty, _data_queue);
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
    std::lock_guard<std::mutex> locker(_mutex);
    if (!isFull())
    {
      _data_queue.push(new_value);
      _condition.notify_one();
      ret = true;
    }
    return ret;
  }
  bool waitPop(T &value) override
  {
    bool ret = false;
    std::unique_lock<std::mutex> locker(_mutex);
    _condition.wait(locker, [this] { return !_data_queue.empty(); });
    value = _data_queue.front();
    _data_queue.pop();
    return true;
  }
  std::shared_ptr<T> waitPop() override
  {
    std::unique_lock<std::mutex> locker(_mutex);
    _condition.wait(locker, [this] { return !_data_queue.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(_data_queue.front()));
    _data_queue.pop();
    return res;
  }
  bool tryPop(T &value) override
  {
    std::lock_guard<std::mutex> locker(_mutex);
    if (_data_queue.empty())
      return false;
    value = _data_queue.front();
    _data_queue.pop();
    return true;
  }

  std::shared_ptr<T> tryPop() override
  {
    std::lock_guard<std::mutex> locker(_mutex);
    if (_data_queue.empty())
      return std::shared_ptr<T>();
    std::shared_ptr<T> res(std::make_shared<T>(_data_queue.front()));
    _data_queue.pop();
    return res;
  }
  void setSize(int size)
  {
    _maxQueueSize = size;
  }
};