/**
 * @file version.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-31
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#define VERSION_MAJOR (1)
#define VERSION_MINOR (0)

#include <ctime>
#include <iostream>
#include <stdint.h>
#include <string>

class BuildDateTime
{
private:
    const std::string BuildDate;
    const std::string BuildTime;

public:
    uint8_t version_major = VERSION_MAJOR;
    uint32_t version_mid = VERSION_MINOR;
    uint32_t version_minor;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t second;
    BuildDateTime() : BuildDate(__DATE__), BuildTime(__TIME__)
    {
        int pos[2];

        pos[0] = BuildDate.find_first_of(" ");
        pos[1] = BuildDate.find_last_of(" ");
        if ("Jan" == BuildDate.substr(0, pos[0]))
            month = 1;
        else if ("Feb" == BuildDate.substr(0, pos[0]))
            month = 2;
        else if ("Mar" == BuildDate.substr(0, pos[0]))
            month = 3;
        else if ("Apr" == BuildDate.substr(0, pos[0]))
            month = 4;
        else if ("May" == BuildDate.substr(0, pos[0]))
            month = 5;
        else if ("Jun" == BuildDate.substr(0, pos[0]))
            month = 6;
        else if ("Jul" == BuildDate.substr(0, pos[0]))
            month = 7;
        else if ("Aug" == BuildDate.substr(0, pos[0]))
            month = 8;
        else if ("Sep" == BuildDate.substr(0, pos[0]))
            month = 9;
        else if ("Oct" == BuildDate.substr(0, pos[0]))
            month = 10;
        else if ("Nov" == BuildDate.substr(0, pos[0]))
            month = 11;
        else if ("Dec" == BuildDate.substr(0, pos[0]))
            month = 12;
        else
        {
            month = 0;
            std::cout << "version : get build month error" << std::endl;
        }

        try
        {
            day = std::stoi(BuildDate.substr(pos[0], pos[1] - pos[0]));
            year = std::stoi(BuildDate.substr(pos[1]));
        }
        catch (std::invalid_argument &) // 若不能进行转换则为 std::invalid_argument
        {
            day = 0;
            year = 0;
            std::cout << "version : get build day error :invalid_argument" << std::endl;
        }
        catch (std::out_of_range &) // 若转换值会落在结果类型的范围外，或若底层函数（ std::strtol 或 std::strtoll ）设置 errno 为 ERANGE 则为 std::out_of_r
        {
            day = 0;
            year = 0;
            std::cout << "version : get build day error： out_of_range" << std::endl;
        }
        catch (...)
        {
            day = 0;
            year = 0;
            std::cout << "version : get build day error： othres" << std::endl;
        }

        pos[0] = BuildTime.find_first_of(":");
        pos[1] = BuildTime.find_last_of(":");

        try
        {
            hour = std::stoi(BuildTime.substr(0, pos[0]));
            min = std::stoi(BuildTime.substr(pos[0] + 1, pos[1] - pos[0]));
            second = std::stoi(BuildTime.substr(pos[1] + 1));
        }
        catch (std::invalid_argument &) // 若不能进行转换则为 std::invalid_argument
        {
            hour = 0;
            min = 0;
            second = 0;
            std::cout << "version : get build time error :invalid_argument" << std::endl;
        }
        catch (std::out_of_range &) // 若转换值会落在结果类型的范围外，或若底层函数（ std::strtol 或 std::strtoll ）设置 errno 为 ERANGE 则为 std::out_of_r
        {
            hour = 0;
            min = 0;
            second = 0;
            std::cout << "version : get build time error： out_of_range" << std::endl;
        }
        catch (...)
        {
            hour = 0;
            min = 0;
            second = 0;
            std::cout << "version : get build time error： othres" << std::endl;
        }

        //用编译时的time_t做为子版本号
        struct tm stTm;
        time_t t_of_day;
        stTm.tm_year = year - 1900;
        stTm.tm_mon = month;
        stTm.tm_mday = day;
        stTm.tm_hour = hour;
        stTm.tm_min = min;
        stTm.tm_sec = second;
        stTm.tm_isdst = 0;
        t_of_day = mktime(&stTm);
        version_minor = t_of_day;
    }
    ~BuildDateTime(){};
};
