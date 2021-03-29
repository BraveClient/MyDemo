/**
 * @file bd.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "bdMsg.hpp"
#include <stdio.h>

BD_MSG::BD_MSG()
{
}

BD_MSG::~BD_MSG()
{
}

void BD_MSG::packageMsg(std::string &outputMsg, const ST_BDMSG inputMsg)
{
    uint16_t length = 0;
    uint8_t sum = 0;

    outputMsg.clear();
    outputMsg.append(inputMsg.command);
    length = htons(inputMsg.length);
    outputMsg.append((char *)&length, sizeof(length));
    uint32_t userAddr = htonl(inputMsg.userAddr);
    outputMsg.append(((char *)&userAddr) + 1, 3);
    outputMsg.append(inputMsg.body);
    sum = 0;
    for (auto ch : outputMsg)
    {
        sum ^= ch;
    }

    outputMsg.append(1, sum);
    outputMsg.append("\r\n"); //??????
    printStr(outputMsg);
}

bool BD_MSG::unpackageMsg(ST_BDMSG &outputMsg, const std::string inputMsg)
{
    uint8_t sum = 0;
    uint32_t offset = 0;
    uint32_t userAddr = 0;
    std::string tempStr;
    uint32_t bodyLength = 0;
    sum = 0;
    for (int i = 1; i < inputMsg.size() - 1; i++)
    {
        sum ^= inputMsg[i];
    }
    if (sum != inputMsg.back())
    {
        return false;
    }

    tempStr = inputMsg.substr(offset, 5);
    offset += 5;
    outputMsg.command = tempStr;
    tempStr = inputMsg.substr(offset, 2);
    offset += 2;
    memcpy(&outputMsg.length, tempStr.data(), sizeof(outputMsg.length));
    outputMsg.length = ntohs(outputMsg.length);
    tempStr = inputMsg.substr(offset, 3);
    offset += 3;
    memcpy(((char *)&userAddr) + 1, tempStr.data(), 3);
    outputMsg.userAddr = ntohl(userAddr);
    bodyLength = inputMsg.size() - offset - 1;
    if (bodyLength < 0)
    {
        return false;
    }
    outputMsg.body = inputMsg.substr(offset, bodyLength);
    return true;
}

void BD_MSG::processData(std::string inputMsg)
{
    ST_BDMSG bdMsg;
    unpackageMsg(bdMsg, inputMsg);
    if ("$ZJXX" == bdMsg.command) //自检信息
    {
        ZJXX(bdMsg.body);
    }
    else if ("$SJXX" == bdMsg.command) //时间信息
    {
        SJXX(bdMsg.body);
    }
    else if ("$FKXX" == bdMsg.command) //反馈信息
    {
        FKXX(bdMsg.body);
    }
    else if ("$ICXX" == bdMsg.command) //IC 信息
    {
        ICXX(bdMsg.body);
    }
    else if ("$DWXX" == bdMsg.command) //定位信息
    {
        DWXX(bdMsg.body);
    }
    else if ("$TXXX" == bdMsg.command) //通信信息
    {
        TXXX(bdMsg.body);
    }
}

void BD_MSG::sendMsg(uint32_t usrAddr, std::string msg, bool ifReq)
{
    TXSQ(usrAddr, msg, ifReq);
}

bool BD_MSG::ZJXX(std::string inputMsg)
{ //to do:
    return false;
}

bool BD_MSG::SJXX(std::string inputMsg)
{ //to do:
    return false;
}

bool BD_MSG::FKXX(std::string inputMsg)
{
    if (5 != inputMsg.size())
        return false;
    ST_FKXX msg;
    std::string tempStr;
    msg.sign = inputMsg[0];
    memcpy(&msg.appendMsg, inputMsg.data() + 1, 4);
    printStr(inputMsg);
    return true;

    // 0x00－成功对应指令的四个 ASCII 字符
    // 0x01－失败对应指令的四个 ASCII 字符
    // 0x02－信号未锁定
    // 0x03－发射被抑制
    // 0x04－发射频度未到需要等待的时间（秒）
    // 0x05－加解密错误
    // 0x06－CRC 错误 对应指令的四个ASCII 字符（如DWXX、TXHZ、DSJG）
    // 0x07－用户机被抑制
    // 0x08－ 抑制解除
}

bool BD_MSG::ICXX(std::string inputMsg)
{ //to do:
    return false;
}

bool BD_MSG::DWXX(std::string inputMsg)
{ //to do:
    return false;
}

bool BD_MSG::TXXX(std::string inputMsg)
{
    ST_TXXX msg;
    uint32_t offset = 0;
    std::string tempStr;
    uint32_t sendaddr = 0;
    uint16_t msgLength = 0;
    msg.msgType = inputMsg[0];
    offset += 1;
    tempStr = inputMsg.substr(offset, 3);
    offset += 3;
    memcpy(((char *)&sendaddr) + 1, tempStr.data(), tempStr.size());
    msg.sendAddr = ntohl(sendaddr);
    msg.sendTime_h = inputMsg[offset];
    msg.sendTime_m = inputMsg[offset + 1];
    offset += 2;
    tempStr = inputMsg.substr(offset, 2);
    offset += 2;
    memcpy(&msgLength, tempStr.data(), tempStr.size());
    msg.msgLength = ntohs(msgLength);
    msg.msgBody = inputMsg.substr(offset, msg.msgLength / 8);
    offset += msg.msgLength;
    msg.crc = inputMsg.back();
    return true;
}

void BD_MSG::GLJC()
{
    //TODO:
    //24 58 54 5A 4A 00 0D 00 00 00 00 00 35 0D 0A
}

void BD_MSG::ICJC()
{
    //TODO:
    //24 49 43 4A 43 00 0C 00 00 00 00 2B 0D 0A
}

void BD_MSG::DWSQ()
{
    //TODO:
    // 24 44 57 53 51 00 16 00 00 00 04 00 00 00 00 00 00 00 00 00 00 27 0D 0A
}

void BD_MSG::SJSC()
{
    //TODO:
    //24 53 4A 53 43 00 0D 00 00 00 00 01 21 0D 0A
}

void BD_MSG::TXSQ(uint32_t usrAddr, std::string inputMsg, bool ifReq)
{
    ST_BDMSG msg;
    uint32_t usrAddr_Big;
    uint16_t msgLength_big;
    {
        msg.body.append(1, 0x46);
        usrAddr_Big = htonl(usrAddr);
        msg.body.append(((char *)&usrAddr_Big) + 1, 3);
        msgLength_big = htobe16(inputMsg.size() * 8);
        msg.body.append(((char *)&msgLength_big), 2);
        msg.body.append(1, 0x0);
        msg.body += inputMsg;
    }
    msg.command = "$TXSQ";
    msg.length = 10 + msg.body.size() + 1;
    msg.userAddr = 0;
    std::string outMsg;
    packageMsg(outMsg, msg);
}

void BD_MSG::printStr(std::string inputMsg)
{
    for (auto ch : inputMsg)
    {
        printf("%02x ", ch);
    }
    printf("\n");
}