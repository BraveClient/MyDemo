/**
 * @file bd.hpp
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
#include <cstring>
#include <arpa/inet.h>
#include <stdlib.h>
#include <endian.h>
#include <stdint.h>

#include "../../include/driverMode.h"

const std::string SEND_MSG_HEADER[] = {
    "$GLJC", //功率检测
    "$DWSQ", //定位申请
    "$TXSQ", //通信申请
    "$HXSZ", //航线设置
    "$DHSQ", // 导航申请
    "$DSSQ", //定时申请
    "$SCSC", //时差输出
    "$ZBZH", //坐标转换
    "$JSZL", //结束指令
    "$WMCS", //误码测试
    "$CKSC", //串口输出
    "$ICJC", //IC 检测
    "$JJZH", //紧急自毁
    "$BSSZ", //波束设置
    "$GXZX", //管信注入
    "$GXDQ", //管信读取
    "$XTZJ", //系统自检
    "$LZSZ", //零值设置
    "$LZDQ", //零值读取
    "$SJSC", //时间输出
    "$BBDQ", //版本读取
    "$XHDQ"  //序号读取
};

const std::string RECV_MSG_HEADER[] = {
    "$GLZK", //功率状况
    "$DWXX", //定位信息
    "$TXXX", //通信信息
    "$TXHZ", //通信回执
    "$KLSB", //口令识别
    "$DHSC", //导航输出
    "$DSJG", //定时结果
    "$SCSJ", //时差数据
    "$ZBSC", //坐标输出
    "$GBSC", //广播输出
    "$GYSC", //公用输出
    "$ICXX", //IC 信息
    "$ZHQR", //自毁确认
    "$ZJXX", //自检信息
    "$LZXX", //零值信息
    "$SJXX", //时间信息
    "$BBXX", //版本信息
    "$XHXX", //序号信息
    "$FKXX", //反馈信息
    "$QLXX", //I 路信息
    "$QLXX" // Q 路信息
};

typedef struct
{
    std::string command;
    uint16_t length;
    uint32_t userAddr;
    std::string body;
    uint8_t sum;
} ST_BDMSG;

typedef struct
{
    uint8_t msgType;
    uint32_t sendAddr;
    uint8_t sendTime_h;
    uint8_t sendTime_m;
    uint16_t msgLength;
    std::string msgBody;
    uint8_t crc;
} ST_TXXX;

typedef struct
{
    uint8_t sign;
    uint32_t appendMsg;
} ST_FKXX;

typedef struct
{
    uint8_t msgType;
    uint32_t userAddr;
    uint16_t msgLength;
    uint8_t ifReq;
    std::string msgBody;
} ST_TXSQ;

class BD_MSG:public driverMode
{
private:
    void packageMsg(std::string &outputMsg, const ST_BDMSG inputMsg);
    bool unpackageMsg(ST_BDMSG &outputMsg, const std::string inputMsg);
    bool ZJXX(std::string inputMsg);
    bool SJXX(std::string inputMsg);
    bool FKXX(std::string inputMsg);
    bool ICXX(std::string inputMsg);
    bool DWXX(std::string inputMsg);
    bool TXXX(std::string inputMsg);
    void printStr(std::string inputMsg);

public:
    BD_MSG(/* args */);
    ~BD_MSG();
    void processData(std::string inputMsg);
    void sendMsg(uint32_t usrAddr, std::string msg, bool ifReq = false);
    void GLJC(); //功率检测
    void ICJC(); //IC 检测
    void DWSQ(); //定位申请
    void SJSC(); //时间输出
    void TXSQ(uint32_t usrAddr, std::string msg, bool ifReq = false); //通信申请
};