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

#define LED_POWER_GPIO (2)


class Led : public driverMode
{
private:
    


public:
    Led();
    ~Led();
    

    bool init() override;
    bool powerOn() override;
    bool powerOff() override;
    bool powerChange(bool power) override;
    bool power() override;


};
