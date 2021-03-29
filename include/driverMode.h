/**
 * @file driverMode.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

class driverMode
{
protected:
    bool _power = false;
    int _workStatus = 0;

public:
    driverMode();
    virtual ~driverMode() = default;

    virtual bool powerOn() { return true; };
    virtual bool powerOff() { return true; };
    virtual bool powerChange(bool power) { return true; };
    virtual bool power() { return true; };
    virtual bool selfCheck() { return _workStatus; };
    virtual bool selfCheck(bool check) { return selfCheck(); };
    virtual bool init() { return true; };
};
