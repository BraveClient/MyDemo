/**
 * @file dataStorePack.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

#include <string>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "../../libs/crc/crc.h"
#include "../../include/version.h"

enum EN_MSG_TYPE
{
    EN_MSG_TYPE_START = 0,
    EN_MSG_TYPE_TIME = 1,
    EN_MSG_TYPE_DATA = 2
};

/**
 * @brief  包头
 * 
 */
#pragma packed(1)
typedef struct
{
    uint16_t startSignal; // == 0xffff
    uint8_t msgType;
    uint8_t msgNum;
    uint16_t msgbodyLen;
    uint16_t msgLen;
    uint64_t tick : 48;
    uint64_t msgHeaderCrc16 : 16;

} ST_PACKAGE_HEADER;
#pragma packed()

/**
 * @brief 包尾
 * 
 */
#pragma packed(1)
typedef struct
{
    uint32_t space : 16;
    uint32_t crc16 : 16;
} ST_PACKAGE_TAILER;
#pragma packed()

/**
 * @brief 包体
 * 
 */
typedef struct
{
    std::string msg;
} ST_PACKAGE_BODY;

/**
 * @brief 全包
 * 
 */
typedef struct
{
    ST_PACKAGE_HEADER header;
    ST_PACKAGE_BODY body;
    ST_PACKAGE_TAILER tailer;
} ST_PACKAGE;

/**
 * @brief 起始包
 * 
 */
#pragma packed(1)
typedef struct
{
    uint32_t version_h : 8; //0
    uint32_t version_l : 8;
    uint32_t year : 16;
    uint32_t month : 8; //1
    uint32_t day : 8;
    uint32_t hour : 8;
    uint32_t minute : 8;
    uint32_t second : 8; //2
    uint32_t space : 24;
} ST_PACKAGE_BODY_START;
#pragma packed()

/**
 * @brief 时间包
 * 
 */
#pragma packed(1)
typedef struct
{
    uint32_t year : 16; //0
    uint32_t month : 8;
    uint32_t day : 8;
    uint32_t hour : 8; //1
    uint32_t minute : 8;
    uint32_t second : 8;
    uint32_t space : 8;
    uint32_t ticksInSecond;
} ST_PACKAGE_BODY_TIME;

#pragma packed()

class DataStoragePack
{
public:
    static bool unPack(ST_PACKAGE &destMsg, const std::string &srcMsg);
    static bool packData(std::string &destMsg, const std::string &srcMsg,EN_MSG_TYPE type = EN_MSG_TYPE_DATA);
    static bool packFirst(std::string &destMsg);
    static bool packTime(std::string &destMsg);

private:
    static uint8_t packNum;
    DataStoragePack(std::string) {}
    ~DataStoragePack(){};
};