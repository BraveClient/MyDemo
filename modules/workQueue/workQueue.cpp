/**
 * @file workQueue.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "workQueue.hpp"
using namespace std;

workQueue *workQueue::_pInstance = new workQueue();

workQueue::workQueue()
{
    // _events.clear();
}

workQueue::~workQueue()
{
}

bool workQueue::init()
{
    return true;
}

void workQueue::run()
{
    log_trace("---------------------------thread start-------------------------------");
    uint32_t usSleepTime=1000000; //1s
    // ST_EVENT eventNow = {{0,0},nullptr};

    // clock_gettime(CLOCK_MONOTONIC, &eventNow.mstimer);
    // for (auto &task : _workQueue)
    // {
    //     task.mstimer = eventNow.mstimer;
    // }


    log_trace("---------------------------thread run-------------------------------");
    while (_runSta)
    {
        // clock_gettime(CLOCK_MONOTONIC, &eventNow.mstimer);
        

        usleep(usSleepTime);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
// #define EVENT_IMMEDIATELY_EXECUTE (unsigned int)0
// #define EP_EVENT_NUM_MAX (unsigned int)29

// /**
//  * @brief 事件处理函数指针类型
//  *
//  */
// typedef void (*EP_EventHandler)();

// /**
//  * @brief 事件结构体
//  *
//  */
// typedef struct
// {
//     uint32_t ustimer;              /**< 事件执行周期*/
//     EP_EventHandler pEventHandler; /**< 事件处理函数指针*/
// } EP_EVENT;

// /**
// 事件列表
// */
// EP_EVENT EP_gEventList[EP_EVENT_NUM_MAX];
// /**
// 实际注册事件数
// */
// unsigned int EP_event_num = 0;

// /**
//  * @brief 注册事件处理函数接口
//  *
//  * @param pFun 事件处理函数指针
//  * @param period 事件执行周期
//  */
// // struct timespec time1 = {0, 0};
// // clock_gettime(CLOCK_MONOTONIC, &time1);

// void EP_register_event_handler(EP_EventHandler pFun, unsigned int period)
// {
//     if (pFun == NULL)
//         return;
//     if (EP_event_num > EP_EVENT_NUM_MAX)
//         return;
//     if (period < 50 && period > 0)
//         return;

//     int event_id = -1;
//     //获取事件ID
//     event_id = EP_get_event_id(pFun);

//     if (event_id == -1) //新注册事件
//     {
//         //初始化定时器
//         timer_init(&(EP_gEventList[EP_event_num].timer), period);
//         EP_gEventList[EP_event_num].timer.id = EP_event_num + 1; //定时器ID
//         event_id = EP_event_num + 1;                             //事件ID
//         //注册函数
//         EP_gEventList[EP_event_num].pEventHandler = pFun;
//         EP_event_num++;
//     }
//     else
//     {
//         //初始化定时器
//         timer_init(&(EP_gEventList[event_id].timer), period);
//         //更新函数
//         EP_gEventList[event_id].pEventHandler = NULL;
//         EP_gEventList[event_id].pEventHandler = pFun;
//     }
// }

// /**
//  * @brief 轮询注册的事件，调用到期事件
//  *
//  */
// void workQueue::EP_poll()
// {
//     _workqueue.front()

//     unsigned int i = 0;
//     for (i = 0; i < _workqueue.size(); i++)
//     {
//         if (EP_gEventList[i].pEventHandler != NULL)
//         {
//             if (EP_gEventList[i].timer.period > 0) //周期执行事件
//             {
//                 //定时时间到
//                 if (is_timer_up(&(EP_gEventList[i].timer)))
//                 {
//                     EP_gEventList[i].pEventHandler();
//                 }
//             }
//             else //立即执行事件
//             {
//                 EP_gEventList[i].pEventHandler();
//             }
//         }
//     }
// }

// /**
//  * @brief 查找注册的事件ID
//  *
//  * @param pFun 事件回调函数指针
//  * @return int 事件ID
//  */
// int EP_get_event_id(EP_EventHandler pFun)
// {
//     unsigned int i = 0;
//     for (i = 0; i < EP_event_num; i++)
//     {
//         if (EP_gEventList[i].pEventHandler == pFun)
//         {
//             return (int)i;
//         }
//     }
//     return -1;
// }
