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
//  * @brief �¼�������ָ������
//  *
//  */
// typedef void (*EP_EventHandler)();

// /**
//  * @brief �¼��ṹ��
//  *
//  */
// typedef struct
// {
//     uint32_t ustimer;              /**< �¼�ִ������*/
//     EP_EventHandler pEventHandler; /**< �¼�������ָ��*/
// } EP_EVENT;

// /**
// �¼��б�
// */
// EP_EVENT EP_gEventList[EP_EVENT_NUM_MAX];
// /**
// ʵ��ע���¼���
// */
// unsigned int EP_event_num = 0;

// /**
//  * @brief ע���¼��������ӿ�
//  *
//  * @param pFun �¼�������ָ��
//  * @param period �¼�ִ������
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
//     //��ȡ�¼�ID
//     event_id = EP_get_event_id(pFun);

//     if (event_id == -1) //��ע���¼�
//     {
//         //��ʼ����ʱ��
//         timer_init(&(EP_gEventList[EP_event_num].timer), period);
//         EP_gEventList[EP_event_num].timer.id = EP_event_num + 1; //��ʱ��ID
//         event_id = EP_event_num + 1;                             //�¼�ID
//         //ע�ắ��
//         EP_gEventList[EP_event_num].pEventHandler = pFun;
//         EP_event_num++;
//     }
//     else
//     {
//         //��ʼ����ʱ��
//         timer_init(&(EP_gEventList[event_id].timer), period);
//         //���º���
//         EP_gEventList[event_id].pEventHandler = NULL;
//         EP_gEventList[event_id].pEventHandler = pFun;
//     }
// }

// /**
//  * @brief ��ѯע����¼������õ����¼�
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
//             if (EP_gEventList[i].timer.period > 0) //����ִ���¼�
//             {
//                 //��ʱʱ�䵽
//                 if (is_timer_up(&(EP_gEventList[i].timer)))
//                 {
//                     EP_gEventList[i].pEventHandler();
//                 }
//             }
//             else //����ִ���¼�
//             {
//                 EP_gEventList[i].pEventHandler();
//             }
//         }
//     }
// }

// /**
//  * @brief ����ע����¼�ID
//  *
//  * @param pFun �¼��ص�����ָ��
//  * @return int �¼�ID
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
