/**
 * @file sideScan.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "../../include/driverMode.h"
#include "../../libs/NMEA0183/nmea0183.h"
#include <wiringPi.h>
#include <string>
#include <array>

#define SIDESCAN_SONAR_POWER_GPIO (2)

enum class EN_SD_ON
{
    SD_ON_RASPI,
    SD_ON_SIDESCAN
};

class sideScan : public driverMode
{
private:
    float _temperature;

    enum EN_SIDESCAN_ACTION
    {
        ACTION_SD_RASPI=0,
        ACTION_SD_SIDESCAN,
        ACTION_POWER_ON,
        ACTION_POWER_OFF,
        ACTION_START,
        ACTION_SHUTDOWN,
    };

    enum EN_SIDESCAN_STATUS
    {
        EN_POWER_OFF=0,
        EN_POWER_ON,
        EN_POWER_ACTION_OFF,
        EN_POWER_ACTION_ON,
        EN_ERROR
    };



    enum EN_SIDESCAN_STATUS _status;
    int _actionNum;

    const char _sd2Raspi[4] = {0x55, 0xaa, 0x01, 0x01};
    const char _sd2sidescan[4] = {0x55, 0xaa, 0x01, 0x00};
    const char _powerOn[4] = {0x55, 0xaa, 0x02, 01};
    const char _powerOff[4] = {0x55, 0xaa, 0x02, 0x00};
    const char _sidescanStart[4] = {0x55, 0xaa, 0x03, 0x01};
    const char _sidescanShutdown[4] = {0x55, 0xaa, 0x01, 0x00};
    const int powerOnArray[3] = {ACTION_SD_SIDESCAN, ACTION_POWER_ON, ACTION_START};
    const int powerOffArray[3] = {ACTION_SHUTDOWN, ACTION_POWER_OFF, ACTION_SD_RASPI};

public:
    sideScan();
    ~sideScan();

    bool init() override;
    bool powerOn() override;
    bool powerOff() override;
    bool powerChange(bool power) override;
    bool power() override;
    bool selfCheck() override;
    bool selfCheck(bool check) override;

    bool getPowerSendString(std::string &str);
    bool setSidescanNMEA0183(const std::string &str);
};
