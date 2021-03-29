/**
 * @file autoDriver.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include "../../include/module.h"
#include "../../include/log.hpp"
#include "../../include/json.hpp"
#include "../../libs/assistant/assistant.h"

#include <string>
#include <atomic>
enum class EN_OPERATION_TYPE
{
    Y10H_controlMode_NULL = 0x00,             //无效
    Y10H_controlMode_DirectionControl = 0x01, //航行寻向控制
    Y10H_controlMode_PositonControl = 0x02,   //航行寻点控制
    Y10H_controlMode_HoverControl = 0x03,     //航行悬停控制
    Y10H_controlMode_CycleControl = 0x04,     //旋回模式
    Y10H_controlMode_Manual = 0x05
};

class AutoDriver : public module
{
public:
    static AutoDriver *getInstance() { return _pInstance; }
    bool init();

    bool setTask(const std::string &taskFileName);
    bool setTask(const nlohmann::json workTask);
    bool stopTask();

private:
    AutoDriver();
    AutoDriver(const AutoDriver &) = delete;
    AutoDriver &operator=(const AutoDriver &) = delete;
    ~AutoDriver();
    void run() override;
    bool taskOptCheck();
    bool runAction();

private:
    static AutoDriver *_pInstance;

    std::atomic<bool> _isInTask;
    nlohmann::json _workTaskActions;
    nlohmann::json _workTaskOpt;
};
