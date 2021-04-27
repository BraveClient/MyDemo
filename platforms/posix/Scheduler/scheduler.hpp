/**
 * @file scheduler.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include "../moduleBase.hpp"
#include <list>
#include <semaphore.h>

#define ADD_TASK_IN_SCHEDULER(name, frequency, sem) \
    {                                               \
        Scheduler *p = Scheduler::getInstance();    \
        p.addTask(##name, frequency, sem)           \
    }

class Scheduler : public ModuleBase
{
private:
    static Scheduler *_pInstance;
    struct task
    {
        std::string name;
        float frequency;
        sem_t sem;
        time_t nextCallTime;
    };
    std::list<struct task> _taskList;

    Scheduler(/* args */);
    ~Scheduler();
    int init();

public:
    static Scheduler *getInstance() { return _pInstance; }

    void run() override;

    int addTask(std::string name, float frequency, sem_t sem);
};
