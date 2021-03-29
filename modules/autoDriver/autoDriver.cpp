/**
 * @file autoDriver.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "autoDriver.hpp"
using namespace std;

AutoDriver *AutoDriver::_pInstance = new AutoDriver();

AutoDriver::AutoDriver()
{
    // _events.clear();
}

AutoDriver::~AutoDriver()
{
}

bool AutoDriver::init()
{
    _isInTask =false;
    return true;
}

void AutoDriver::run()
{
    log_trace("---------------------------thread start-------------------------------");

    log_trace("---------------------------thread run-------------------------------");
    while (_runSta)
    {

        /* 1.self check */
        /* 2.taskOption check */
        
        /* 3.run action */
    }
}

bool AutoDriver::setTask(const std::string& taskFileName)
{
    if (_isInTask)
    {
        return false;
    }
    ifstream jsonFile(taskFileName);
    nlohmann::json taskJson;

    if (!jsonFile.good())
    {
        return false;
    }
    jsonFile >> taskJson;

    _workTaskOpt = taskJson.at("TaskOpt");
    _workTaskActions = taskJson.at("TaskActions");
    jsonFile.close();
    return true;
}
bool AutoDriver::setTask(nlohmann::json workTask)
{
    if (_isInTask)
    {
        return false;
    }
    _workTaskOpt = workTask.at("TaskOpt");
    _workTaskActions = workTask.at("TaskActions");
    return true;
}
bool AutoDriver::stopTask() 
{
    if (!_isInTask)
    {
        return true;
    }
}
