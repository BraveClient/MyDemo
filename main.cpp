/**
 * @file main.cpp
 * @author yh(forgetsky001@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <string>
#include <iostream>
#include <stdio.h>

#include "include/defines.h"
#include "include/module.h"
#include "include/containers/AbstructThreadsafeMethod.hpp"
#include "include/json.hpp"

#include "modules/udpSender/udpSender.hpp"
#include "modules/udpReceiver/udpReceiver.hpp"
#include "modules/wirteFile/wirteFile.hpp"
#include "modules/logger/logger.hpp"
#include "modules/selfcheck/selfcheck.hpp"

#include "libs/globalData/globalData.hpp"
#include "libs/assistant/assistant.h"

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <list>
// #include <wiringPi.h>

using json = nlohmann::json;
using namespace std;

std::list<module *> threadList;

/**
 * @brief 读取主节点JSON信息
 * 
 * @return true 成功
 * @return false 失败
 */
bool initJson()
{
    json masterNodes;
    string exePath;
    std::string masterNodesJosnFilePath;
    char path[1024] = {'\0'};
    GlobalData *globalData = GlobalData::getInstance();

    readlink("/proc/self/exe", path, 1024 - 1);
    exePath = string(path);
    masterNodesJosnFilePath = exePath.substr(0, exePath.find_last_of("/")) + "/../master_nodes.json";

    ifstream jsonFile(masterNodesJosnFilePath);
    if (!jsonFile.good())
    {
        return false;
    }
    jsonFile >> masterNodes;
    jsonFile.close();

    globalData->setMasterNode(masterNodes.at("master_nodes"));
    return true;
}

/**
 * @brief 初始化wiringPi
 * 
 * @return true 成功 
 * @return false 失败
 */
int initWiringPi()
{
    // int ret = wiringPiSetup();
    // return ret;
    return true;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool FW_init()
{
    threadList.clear();
    GlobalData *globalData = GlobalData::getInstance();
    int ret = -1;

    //初始化日志记录
    Logger *logRecorder = Logger::getInstance();
    ret = logRecorder->init(globalData->getLogDataQueue(), "log.txt");
    if (false == ret)
    {
        log_error("log_init error");
        return false;
    }
    threadList.push_back(dynamic_cast<module *>(logRecorder));

    //读取主节点JSON信息
    if (!initJson())
    {
        log_error("read_master_nodes_config error");
        return false;
    }

    // 初始化wiringpi
    if(0 !=initWiringPi())
    {
        log_error("initWiringPi error");
        return false;
    }


    //初始化UDP
    string thisNodeIpAddr;
    uint16_t thisNodePort = 0;

    json dataRecorderNode = globalData->getNode("USDataRecorder");
    if (dataRecorderNode.is_null())
    {
        log_error("error,read this node infomation error!");
        return false;
    }

    thisNodeIpAddr = dataRecorderNode.at("ip");
    thisNodePort = dataRecorderNode.at("port");
    if (thisNodeIpAddr.empty() || 0 == thisNodePort)
    {
        log_error("error,read masterNode error!");
        return false;
    }
    module *sender = new udpSender(globalData->getUdpSendQueue(), thisNodeIpAddr, 3000);
    module *recver = new udpReceiver(globalData->getUdpRecvSaveQueue(), globalData->getUdpRecvDataQueue(), thisNodeIpAddr, thisNodePort);
    threadList.push_back(dynamic_cast<module *>(sender));
    threadList.push_back(dynamic_cast<module *>(recver));

    return true;
}

void FW_run()
{
    for (auto _thread : threadList)
    {
        _thread->start();
    }
    while (1)
    {
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    int ret = 0;

    if (!FW_init())
    {
        log_error("FW_init error");
        return -1;
    }

    GlobalData *globalData = GlobalData::getInstance();

    module *recorder = new wirteFile(globalData->getUdpRecvSaveQueue());
    threadList.push_back(dynamic_cast<module *>(recorder));

    Selfcheck *selfchecker = Selfcheck::getInstance();
    selfchecker->init(globalData->getUdpSendQueue());    
    threadList.push_back(dynamic_cast<module *>(selfchecker));

    FW_run();
}
