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

#include <stdint.h>
#include <string>
#include <iostream>
class VERSION_BUILD
{
private:
    /* data */
public:
    uint8_t version_major = VERSION_MAJOR;
    uint8_t version_minor = VERSION_MINOR;
    uint16_t buildtime_year;
    uint8_t buildtime_mon;
    uint8_t buildtime_day;
    uint8_t buildtime_hour;
    uint8_t buildtime_min;
    uint8_t buildtime_sec;
    VERSION_BUILD()
    {
        int pos[2];
        std::string date(__DATE__);
        std::string time(__TIME__);

        pos[0] = date.find_first_of(" ");
        pos[1] = date.find_last_of(" ");
        if ("Jan" == date.substr(0, pos[0]))
            buildtime_mon = 1;
        else if ("Feb" == date.substr(0, pos[0]))
            buildtime_mon = 2;
        else if ("Mar" == date.substr(0, pos[0]))
            buildtime_mon = 3;
        else if ("Apr" == date.substr(0, pos[0]))
            buildtime_mon = 4;
        else if ("May" == date.substr(0, pos[0]))
            buildtime_mon = 5;
        else if ("Jun" == date.substr(0, pos[0]))
            buildtime_mon = 6;
        else if ("Jul" == date.substr(0, pos[0]))
            buildtime_mon = 7;
        else if ("Aug" == date.substr(0, pos[0]))
            buildtime_mon = 8;
        else if ("Sep" == date.substr(0, pos[0]))
            buildtime_mon = 9;
        else if ("Oct" == date.substr(0, pos[0]))
            buildtime_mon = 10;
        else if ("Nov" == date.substr(0, pos[0]))
            buildtime_mon = 11;
        else if ("Dec" == date.substr(0, pos[0]))
            buildtime_mon = 12;
        else
        {
            buildtime_mon = 0;
            std::cout << "version : get build month error" << std::endl;
        }

        try
        {
            buildtime_day = std::stoi(date.substr(pos[0], pos[1] - pos[0]));
            buildtime_year = std::stoi(date.substr(pos[1]));
        }
        catch (std::invalid_argument &) // 若不能进行转换则为 std::invalid_argument
        {
            buildtime_day = 0;
            buildtime_year = 0;
            std::cout << "version : get build day error :invalid_argument" << std::endl;
        }
        catch (std::out_of_range &) // 若转换值会落在结果类型的范围外，或若底层函数（ std::strtol 或 std::strtoll ）设置 errno 为 ERANGE 则为 std::out_of_r
        {
            buildtime_day = 0;
            buildtime_year = 0;
            std::cout << "version : get build day error： out_of_range" << std::endl;
        }
        catch (...)
        {
            buildtime_day = 0;
            buildtime_year = 0;
            std::cout << "version : get build day error： othres" << std::endl;
        }

        pos[0] = time.find_first_of(":");
        pos[1] = time.find_last_of(":");

        try
        {
            buildtime_hour = std::stoi(time.substr(0, pos[0]));
            buildtime_min = std::stoi(time.substr(pos[0] + 1, pos[1] - pos[0]));
            buildtime_sec = std::stoi(time.substr(pos[1]+1));
        }
        catch (std::invalid_argument &) // 若不能进行转换则为 std::invalid_argument
        {
            buildtime_hour = 0;
            buildtime_min = 0;
            buildtime_sec = 0;
            std::cout << "version : get build time error :invalid_argument" << std::endl;
        }
        catch (std::out_of_range &) // 若转换值会落在结果类型的范围外，或若底层函数（ std::strtol 或 std::strtoll ）设置 errno 为 ERANGE 则为 std::out_of_r
        {
            buildtime_hour = 0;
            buildtime_min = 0;
            buildtime_sec = 0;
            std::cout << "version : get build time error： out_of_range" << std::endl;
        }
        catch (...)
        {
            buildtime_hour = 0;
            buildtime_min = 0;
            buildtime_sec = 0;
            std::cout << "version : get build time error： othres" << std::endl;
        }
    }
    ~VERSION_BUILD(){};
};
