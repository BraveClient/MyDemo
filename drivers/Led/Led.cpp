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
#include "Led.hpp"

Led::Led(/* args */)
{
    init();
}

Led::~Led()
{
    digitalWrite(LED_POWER_GPIO, LOW);
}

bool Led::init()
{
    pinMode(LED_POWER_GPIO, OUTPUT);
    digitalWrite(LED_POWER_GPIO, LOW);
    _power = false;
    return true;
}

bool Led::powerOn()
{
    if (0 == digitalRead(LED_POWER_GPIO))
    {
        digitalWrite(LED_POWER_GPIO, HIGH);
    }
    return true;
}

bool Led::powerOff()
{
    if (1 == digitalRead(LED_POWER_GPIO))
    {
        digitalWrite(LED_POWER_GPIO, LOW);
    }
    return true;
}
bool Led::powerChange(bool power)
{
    if (power != digitalRead(LED_POWER_GPIO))
    {
        digitalWrite(LED_POWER_GPIO, power);
    }
    return true;
}
bool Led::power()
{
    return digitalRead(LED_POWER_GPIO);
}