/**
 * @file module.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <thread>
#pragma once

class ModuleBase
{
public:
    bool _running = false;
    std::thread _thread;
    ModuleBase() {}
    virtual ~ModuleBase() {}
    void start()
    {
        _running = true;
        _thread = std::thread(&ModuleBase::run, this);
    }
    void stop()
    {
        //FIXME when wait in mutex ,can not stop
        if (true == _running)
        {
            _running = false;
        }
        _thread.join();
    }
    inline bool isRun() { return _running; }
    virtual void run() { _running = false; };
};