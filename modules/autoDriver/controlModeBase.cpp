/**
 * @file controlModeBase.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "controlModeBase.hpp"

ControlModeBase::ControlModeBase(nlohmann::json &actionJson) : _actionJson(actionJson)
{
}

ControlModeBase::~ControlModeBase()
{
}

/**
 * @brief 检查动作是否格式正确
 * 
 * @return true 
 * @return false 
 */
bool ControlModeBase::init()
{
    /* 1 动作号 */
    if (_actionJson.end() == _actionJson.find("num"))
    {
        return false;
    }
    else
    {
        _num = _actionJson.find("num").value().get<uint32_t>();
    }
    /* 2 动作模式 */
    if (_actionJson.end() == _actionJson.find("controlMode"))
    {
        return false;
    }
    else if (_actionJson.at("controlMode").end() == _actionJson.at("controlMode").find("type"))
    {
        return false;
    }
    else
    {
        _controlMode = _actionJson.at("controlMode").at("type").get<uint32_t>();
    }
    /* 3 超时条件 */
    if (_actionJson.end() == _actionJson.find("errorCondition"))
    {
        return false;
    }
    else
    {
        if (_actionJson.at("errorCondition").end() == _actionJson.at("errorCondition").find("max_time"))
        {
            return false;
        }
        else
        {
            _errorCondition.maxtime = _actionJson.at("errorCondition").at("max_time").get<uint32_t>();
        }
    }
    /* 4 存在下一步动作 */
    if (_actionJson.end() == _actionJson.find("nextAction"))
    {
        return false;
    }
    else
    {
        if (_actionJson.at("nextAction").end() == _actionJson.at("nextAction").find("satisfied") || _actionJson.at("nextAction").end() == _actionJson.at("nextAction").find("error"))
        {
            return false;
        }
        else
        {
            _nextActionNum.satified = _actionJson.at("nextAction").at("satisfied").get<uint32_t>();
            _nextActionNum.error = _actionJson.at("nextAction").at("error").get<uint32_t>();
        }
    }
    /* 5 存在任务目标 */
    if (_actionJson.end() == _actionJson.find("target"))
    {
        return false;
    }
    else
    {
        if (_actionJson.at("target").size() <= 0)
        {
            return false;
        }
        //又有深度又有对底高度，报错
        if (_actionJson.at("target").end() == _actionJson.at("target").find("depth") && _actionJson.at("target").end() == _actionJson.at("target").find("high"))
        {
            return false;
        }
    }

    _startTimeStamp.initTimenow();
    return true;
}

uint32_t ControlModeBase::ActionRun(EN_CONTROL_MODE_STATUS &status, const ST_VECHILE_POSITION &position)
{
    TimeStamp timenow;
    timenow.initTimenow();
    _runTime_s = (timenow - _startTimeStamp).toSecond();
    bool ret = true;
    float min = 0;
    float max = 0;

    /* 1. check action error run time*/
    uint32_t maxRuntime = _actionJson.find("errorCondition").value().find("max_time").value().get<uint32_t>();
    if (_runTime_s > maxRuntime)
    {
        status = EN_CONTROL_MODE_STATUS::ACTION_STATUS_ERROR;
        return _nextActionNum.error;
    }

    /* 2. satisfied condition */
    if (satisfiedCondition(position))
    {
        status = EN_CONTROL_MODE_STATUS::ACTION_STATUS_ERROR;
        return _nextActionNum.satified;
    }

    /* 3. fill 10H feild */
    writeToCommand();
}

bool ControlModeBase::satisfiedCondition(const ST_VECHILE_POSITION &position)
{
    bool ret = true;
    float min;
    float max;
    //latitude
    if (_actionJson.at("target").end() != _actionJson.at("target").find("latitude"))
    {
        if (2 == _actionJson.at("target").at("latitude").size())
        {
            nlohmann::json &target = _actionJson.at("target").at("latitude");
            min = target.at(1).at(0);
            max = target.at(1).at(1);
            ret &= is_inRange(position.x, min, max);
        }
    }
    //longitude
    if (_actionJson.at("target").end() != _actionJson.at("target").find("longtitude"))
    {
        if (2 == _actionJson.at("target").at("longtitude").size())
        {
            nlohmann::json &target = _actionJson.at("target").at("longtitude");
            min = target.at(1).at(0);
            max = target.at(1).at(1);
            ret &= is_inRange(position.y, min, max);
        }
    }

    //深度对底高度
    if (_actionJson.at("target").end() != _actionJson.at("target").find("depth"))
    {
        if (2 == _actionJson.at("target").at("depth").size())
        {
            nlohmann::json &target = _actionJson.at("target").at("depth");
            min = target.at(1).at(0);
            max = target.at(1).at(1);
            ret &= is_inRange(position.z_Depth, min, max);
        }
    }
    else if (_actionJson.at("target").end() != _actionJson.at("target").find("high"))
    {
        if (2 == _actionJson.at("target").at("high").size())
        {
            nlohmann::json &target = _actionJson.at("target").at("high");
            min = target.at(1).at(0);
            max = target.at(1).at(1);
            ret &= is_inRange(position.z_High, min, max);
        }
    }
    //yaw
    if (_actionJson.at("target").end() != _actionJson.at("target").find("yaw"))
    {
        if (2 == _actionJson.at("target").at("yaw").size())
        {
            nlohmann::json &target = _actionJson.at("target").at("yaw");
            min = target.at(1).at(0);
            max = target.at(1).at(1);
            ret &= is_inRange(position.yaw, min, max);
        }
    }

    //pitch
    if (_actionJson.at("target").end() != _actionJson.at("target").find("pitch"))
    {
        if (2 == _actionJson.at("target").at("pitch").size())
        {
            nlohmann::json &target = _actionJson.at("target").at("pitch");
            min = target.at(1).at(0);
            max = target.at(1).at(1);
            ret &= is_inRange(position.pitch, min, max);
        }
    }

    //roll
    if (_actionJson.at("target").end() != _actionJson.at("target").find("roll"))
    {
        if (2 == _actionJson.at("target").at("roll").size())
        {
            nlohmann::json &target = _actionJson.at("target").at("roll");
            min = target.at(1).at(0);
            max = target.at(1).at(1);
            ret &= is_inRange(position.roll, min, max);
        }
    }

    if (_actionJson.at("target").end() != _actionJson.at("target").find("v_x"))
    {
        if (2 == _actionJson.at("target").at("v_x").size())
        {
            nlohmann::json &target = _actionJson.at("target").at("v_x");
            min = target.at(1).at(0);
            max = target.at(1).at(1);
            ret &= is_inRange(position.v_x, min, max);
        }
    }
}