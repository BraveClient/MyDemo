/**
 * @file controlMode.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include "../../include/json.hpp"
#include <ctime>
#include <unistd.h>
#include "../../include/timeStamp.hpp"
#include "../../libs/netProtocol/net_protocol.h"
#include "../../libs/math/AP_Math.h"

enum class EN_CONTROL_MODE_STATUS
{
    ACTION_STATUS_ERRACTION = 0,
    ACTION_STATUS_RUN = 1,
    ACTION_STATUS_FINISH = 2,
    ACTION_STATUS_ERROR = 3
};

struct ST_VECHILE_POSITION // North,east,sky
{
    float x;       //latitude(north+),degree
    float y;       //longitude(east+),degree
    float z_Depth; //深度[0,100),m
    float z_High;  //对地高度[0,infinite),m
    float yaw;     //航向[-180,180),degree
    float pitch;   //俯仰[-90,90),degree
    float roll;    //横滚[-180,180),degree
    float v_x;     //speed[-infinite,+infinite],m/s
    float v_y;
    float v_Z;
};

class ControlModeBase
{
protected:
    EN_CONTROL_MODE_STATUS _runStatus = EN_CONTROL_MODE_STATUS::ACTION_STATUS_ERRACTION;
    nlohmann::json _actionJson;
    uint32_t _runTime_s;
    TimeStamp _startTimeStamp;

    uint32_t _num = 0;
    uint32_t _controlMode = 0;
    uint32_t _maxRunTime_s = 0;
    struct
    {
        uint32_t maxtime;
    } _errorCondition;
    struct
    {
        uint32_t satified;
        uint32_t error;
    } _nextActionNum;

    

public:
    Y10H_Info _sendMsg;

    ControlModeBase(nlohmann::json &actionJson);
    virtual ~ControlModeBase();
    bool init();
    virtual uint32_t ActionRun(EN_CONTROL_MODE_STATUS &status, const ST_VECHILE_POSITION &position);
    bool satisfiedCondition(const ST_VECHILE_POSITION &position);
    virtual bool writeToCommand()=0;
};

