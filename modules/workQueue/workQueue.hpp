/**
 * @file workQueue.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "../../include/common.h"
#include "../../include/module.h"
#include "../../include/defines.h"
#include "../../include/containers/AbstructThreadsafeMethod.hpp"
#include "../../include/containers/ThreadsafeQueue.hpp"
#include "../../include/containers/ThreadsafeRingBuffer.hpp"
#include "../../libs/globalData/globalData.hpp"
#include "../../libs/netProtocol/net_protocol.h"
#include "../../modules/logger/logger.hpp"
#include "../../include/timeStamp.hpp"
#include <fstream>
#include <stdarg.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <mutex>
#include <list>
#include <ctime>
#include <vector>

typedef void (*EP_EventHandler)();




typedef struct EP_EVENT
{
    TimeStamp nextRunTime;       /*下次执行时间*/
    uint32_t period;
    EP_EventHandler pEventHandler; /*事件处理函数指针*/
} ST_EVENT;

class workQueue : public module
{
public:
    static workQueue *getInstance() { return _pInstance; }

    bool init();

    /**
     * @brief 事件结构体
     * 
     */

private:
    workQueue();
    workQueue(const workQueue &) = delete;
    workQueue &operator=(const workQueue &) = delete;
    ~workQueue();
    void run() override;
    static workQueue *_pInstance;

    std::list<ST_EVENT> _workQueue;

    void EP_poll();
};
