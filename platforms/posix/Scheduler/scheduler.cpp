#include "scheduler.hpp"

Scheduler::Scheduler(/* args */)
{
}

Scheduler::~Scheduler()
{
}

void Scheduler::run()
{
    timenow;
    if (_taskList.front().nextCallTime > timenow)
    {
        while (_taskList.front().nextCallTime > timenow)
        {
            _taskList.front().sem;
            _taskList.pop_front();
        }
    }
    else
    {
        sleep((_taskList.front().nextCallTime - timenow)
    }
}

int Scheduler::addTask(std::string name, float frequency, sem_t sem)
{
    for (auto &&i : _taskList)
    {
        if (i.name == name)
        {
            return -1;
        }
    }
    struct task temp
    {
        name, frequency, sem, 0
    };
    _taskList.push_back(temp);
    return 0;
}