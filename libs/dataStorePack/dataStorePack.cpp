/**
 * @file dataStorePack.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "dataStorePack.hpp"

uint8_t DataStoragePack::packNum = 0;

bool DataStoragePack::unPack(ST_PACKAGE &destMsg, const std::string &srcMsg)
{
    //TODO
    return false;
}
bool DataStoragePack::packData(std::string &destMsg, const std::string &srcMsg, EN_MSG_TYPE type)
{
    ST_PACKAGE_HEADER header = {};
    ST_PACKAGE_TAILER tailer = {0, 0};
    uint16_t msgDataLen = 0; //数据4字节对其后的长度
    struct timespec time1 = {0, 0};
    int npos = 0;

    clock_gettime(CLOCK_MONOTONIC, &time1);

    switch (srcMsg.size() % 4)
    {
    case 0:
        break;
    case 1:
    case 2:
    case 3:
        msgDataLen = srcMsg.size() + (4 - srcMsg.size() % 4);
        break;
    default:
        break;
    };

    header.startSignal = 0xffff; // == 0xffff
    header.msgType = type;
    header.msgNum = packNum++;
    header.msgbodyLen = srcMsg.size();
    header.msgLen = sizeof(ST_PACKAGE_HEADER) + msgDataLen + sizeof(ST_PACKAGE_TAILER);
    header.tick = time1.tv_nsec + time1.tv_sec * 10000000ll;
    header.msgHeaderCrc16 = crc_xmodem((uint8_t *)&header, sizeof(header) - 2);

    tailer.crc16 = crc_xmodem((uint8_t *)destMsg.c_str(), npos);

    destMsg.clear();
    destMsg = std::string((char *)&header, sizeof(header)) + srcMsg + std::string((char *)&tailer, sizeof(tailer));

    return true;
}

bool DataStoragePack::packFirst(std::string &destMsg)
{
    ST_PACKAGE_BODY_START stStart;
    VERSION_BUILD version;
    stStart.version_h = version.version_major;
    stStart.version_l = version.version_minor;
    stStart.year = version.buildtime_year;
    stStart.month = version.buildtime_mon;
    stStart.day = version.buildtime_day;
    stStart.hour = version.buildtime_hour;
    stStart.minute = version.buildtime_min;
    stStart.second = version.buildtime_sec;

    std::string msg((char *)&stStart, sizeof(stStart));
    packData(destMsg, msg, EN_MSG_TYPE_START);
    return true;
}
bool DataStoragePack::packTime(std::string &destMsg)
{
    ST_PACKAGE_BODY_TIME stTime;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stTime.year = ltm->tm_year + 1900;
    stTime.month = ltm->tm_mon + 1;
    stTime.day = ltm->tm_mday;
    stTime.hour = ltm->tm_hour;
    stTime.minute = ltm->tm_min;
    stTime.second = ltm->tm_sec;
    stTime.ticksInSecond = 1000 * 1000;
    std::string msg((char *)&stTime, sizeof(stTime));
    packData(destMsg, msg, EN_MSG_TYPE_TIME);
    return true;
}