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

class module
{
public:
    bool _runSta = false;
    std::thread _thread;
    module() {}
    ~module() {}
    void start()
    {
        _runSta = true;
        _thread = std::thread(&module::run, this);
    }
    void stop()
    {
        //FIXME when wait in mutex ,can not stop
        if (true == _runSta)
        {
            _runSta = false;
        }
        _thread.join();
    }
    bool isRun() { return _runSta; }
    virtual void run() { _runSta = false; };
};