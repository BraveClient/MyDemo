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
#include "LockArraryInterface.hpp"
#include <condition_variable>
#include <mutex>
#include <queue>
#include <unistd.h>

template <typename T, int N>
class LockQueue : public LockArraryInterface<T, N>
{
private:
  std::queue<T> _data_queue;

public:
  LockQueue() {}
  LockQueue(LockQueue const &other)
  {
    std::lock_guard<std::mutex> locker(other._mutex);
    _data_queue = other._data_queue;
    this->_maxSize = other._maxSize;
  }

  bool resize(int size)
  {
    if (!isEmpty())
    {
      return false;
    }
    else
    {
      std::lock_guard<std::mutex> locker(this->_mutex);
      std::queue<T> empty;
      std::swap(empty, _data_queue);
      this->_maxSize = size;
    }
  }

  bool isFull() override
  {
    return (_data_queue.size() >= this->_maxSize);
  }
  bool isEmpty() override
  {
    return (_data_queue.empty());
  }
  void clear() override
  {
    std::lock_guard<std::mutex> locker(this->_mutex);
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
    std::lock_guard<std::mutex> locker(this->_mutex);
    if (!isFull())
    {
      _data_queue.push(new_value);
      this->_condition.notify_one();
      ret = true;
    }
    return ret;
  }
  bool waitPop(T &value) override
  {
    bool ret = false;
    std::unique_lock<std::mutex> locker(this->_mutex);
    this->_condition.wait(locker, [this] { return !_data_queue.empty(); });
    value = _data_queue.front();
    _data_queue.pop();
    return true;
  }
  std::shared_ptr<T> waitPop() override
  {
    std::unique_lock<std::mutex> locker(this->_mutex);
    this->_condition.wait(locker, [this] { return !_data_queue.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(_data_queue.front()));
    _data_queue.pop();
    return res;
  }
  bool tryPop(T &value) override
  {
    std::lock_guard<std::mutex> locker(this->_mutex);
    if (_data_queue.empty())
      return false;
    value = _data_queue.front();
    _data_queue.pop();
    return true;
  }

  std::shared_ptr<T> tryPop() override
  {
    std::lock_guard<std::mutex> locker(this->_mutex);
    if (_data_queue.empty())
      return std::shared_ptr<T>();
    std::shared_ptr<T> res(std::make_shared<T>(_data_queue.front()));
    _data_queue.pop();
    return res;
  }
};