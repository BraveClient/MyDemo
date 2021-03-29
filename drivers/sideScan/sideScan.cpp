/**
 * @file sideScan.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "sideScan.hpp"

sideScan::sideScan(/* args */)
{
    init();
}

sideScan::~sideScan()
{
    digitalWrite(SIDESCAN_SONAR_POWER_GPIO, LOW);
}

bool sideScan::init()
{
    pinMode(SIDESCAN_SONAR_POWER_GPIO, OUTPUT);
    digitalWrite(SIDESCAN_SONAR_POWER_GPIO, HIGH);

    _status = EN_POWER_OFF;
    return true;
}

bool sideScan::powerOn()
{
    _actionNum = 0;
    if (EN_POWER_ON != _status)
    {
        _status = EN_POWER_ACTION_ON;
    }
    return true;
}

bool sideScan::powerOff()
{
    _actionNum = 0;
    if (EN_POWER_OFF != _status)
    {
        _status = EN_POWER_ACTION_OFF;
    }
    return true;
}
bool sideScan::powerChange(bool power)
{
    _actionNum = 0;
    if (power)
    {
        if (EN_POWER_ON != _status)
        {
            _status = EN_POWER_ACTION_ON;
        }
        return true;
    }
    else
    {
        if (EN_POWER_OFF != _status)
        {
            _status = EN_POWER_ACTION_OFF;
        }
        return true;
    }
}
bool sideScan::power()
{
    bool ret;
    switch (_status)
    {
    case EN_POWER_OFF:
    case EN_POWER_ACTION_ON:
        ret = false;
        break;
    case EN_POWER_ON:
    case EN_POWER_ACTION_OFF:
        ret = true;
        break;
    default:
        break;
    }
    return ret;
}

bool sideScan::selfCheck()
{ //TODO: need to check msg ever 5 second
    if (EN_ERROR != _status)
        return true;
    else
        return false;
}

bool sideScan::selfCheck(bool check)
{
    if (check)
    {
        return selfCheck();
    }
    else
    {
        if (EN_ERROR != _status)
            return true;
        else
            return false;
    }
}

bool sideScan::getPowerSendString(std::string &str)
{
    //不在开关机动作中时，直接反回
    if (EN_POWER_ACTION_ON != _status && EN_POWER_ACTION_OFF != _status)
    {
        return false;
    }
    int action;
    str.clear();
    switch (_status)
    {
    case EN_POWER_ACTION_OFF:
        action = powerOffArray[_actionNum];
        break;
    case EN_POWER_ACTION_ON:
        action = powerOnArray[_actionNum];
        break;
    default:
        return false;
    }

    switch (action)
    {
    case ACTION_SD_RASPI:
        str = std::string(_sd2Raspi, 4);
        break;
    case ACTION_SD_SIDESCAN:
        str = std::string(_sd2sidescan, 4);
        break;
    case ACTION_POWER_ON:
        str = std::string(_powerOn, 4);
        break;
    case ACTION_POWER_OFF:
        str = std::string(_powerOff, 4);
        break;
    case ACTION_START:
        str = std::string(_sidescanStart, 4);
        break;
    case ACTION_SHUTDOWN:
        str = std::string(_sidescanShutdown, 4);
        break;
    default:
        return false;
    }
    _actionNum++;
    return true;
}

bool sideScan::setSidescanNMEA0183(const std::string &str)
{
    //TODO:从nmea0183数据中提取出温度和对底高度
    SENTENCE msg;
    msg.Sentence = str;
    if (NMEA0183_BOOLEAN::False == msg.IsChecksumBad(msg.GetNumberOfDataFields()))
    {
        return false;
    }


    return true;
}