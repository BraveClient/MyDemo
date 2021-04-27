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
// #include <string>
#include "platforms/posix/BuildDateTime.h"
#include "platforms/posix/containers/LockArraryInterface.hpp"
#include "platforms/posix/containers/LockQueue.hpp"
#include "platforms/posix/containers/LockRingBuffer.hpp"
#include "platforms/posix/containers/RingBuffer.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    BuildDateTime dataTime;
    std::cout << dataTime.year << std::endl;
    std::cout << dataTime.month << std::endl;
    std::cout << dataTime.day << std::endl;
    std::cout << dataTime.hour << std::endl;
    std::cout << dataTime.min << std::endl;
    std::cout << dataTime.second << std::endl;
    std::cout << "hello world" << std::endl;
    return 0;
}

// #include "platforms/posix/containers/LockQueue.hpp"
// #include "platforms/posix/containers/LockRingBuffer.hpp"
// #include <stdio.h>

// #include "include/defines.h"
// #include "include/module.h"
// #include "include/containers/AbstructThreadsafeMethod.hpp"
// #include "include/json.hpp"

// #include "modules/udpReceiver/udpReceiver.hpp"
// #include "modules/writeFile/writeFile.hpp"
// #include "modules/logger/logger.hpp"

// #include "libs/globalData/globalData.hpp"

// #include <iostream>
// #include <stdio.h>
// #include <unistd.h>
// #include <string>
// #include <fstream>
// #include <list>
// // #include <wiringPi.h>

// using json = nlohmann::json;
// using namespace std;

// std::list<module *> threadList;

// /**
//  * @brief 读取主节点JSON信息
//  *
//  * @return true 成功
//  * @return false 失败
//  */
// bool initJson()
// {
//     json masterNodes;
//     string exePath;
//     std::string masterNodesJosnFilePath;
//     char path[1024] = {'\0'};
//     GlobalData *globalData = GlobalData::getInstance();

//     readlink("/proc/self/exe", path, 1024 - 1);
//     exePath = string(path);
//     masterNodesJosnFilePath = exePath.substr(0, exePath.find_last_of("/")) + "/../master_nodes.json";

//     ifstream jsonFile(masterNodesJosnFilePath);
//     if (!jsonFile.good())
//     {
//         return false;
//     }
//     jsonFile >> masterNodes;
//     jsonFile.close();

//     globalData->setMasterNode(masterNodes.at("master_nodes"));
//     return true;
// }

// /**
//  * @brief 初始化wiringPi
//  *
//  * @return true 成功
//  * @return false 失败
//  */
// int initWiringPi()
// {
//     // int ret = wiringPiSetup();
//     // return ret;
//     return true;
// }

// /**
//  * @brief
//  *
//  * @return true
//  * @return false
//  */
// bool FW_init()
// {
//     threadList.clear();
//     GlobalData *globalData = GlobalData::getInstance();
//     int ret = -1;

//     //初始化日志记录
//     Logger *logRecorder = Logger::getInstance();
//     ret = logRecorder->init(globalData->getLogDataQueue(), "log.txt");
//     if (false == ret)
//     {
//         log_error("log_init error");
//         return false;
//     }
//     threadList.push_back(dynamic_cast<module *>(logRecorder));

//     //读取主节点JSON信息
//     if (!initJson())
//     {
//         log_error("read_master_nodes_config error");
//         return false;
//     }

//     // 初始化wiringpi
//     if(0 !=initWiringPi())
//     {
//         log_error("initWiringPi error");
//         return false;
//     }

//     //初始化UDP
//     string thisNodeIpAddr;
//     uint16_t thisNodePort = 0;

//     json dataRecorderNode = globalData->getNode("USDataRecorder");
//     if (dataRecorderNode.is_null())
//     {
//         log_error("error,read this node infomation error!");
//         return false;
//     }

//     thisNodeIpAddr = dataRecorderNode.at("ip");
//     thisNodePort = dataRecorderNode.at("port");
//     if (thisNodeIpAddr.empty() || 0 == thisNodePort)
//     {
//         log_error("error,read masterNode error!");
//         return false;
//     }
//     module *sender = new udpSender(globalData->getUdpSendQueue(), thisNodeIpAddr, 3000);
//     module *recver = new udpReceiver(globalData->getUdpRecvSaveQueue(), globalData->getUdpRecvDataQueue(), thisNodeIpAddr, thisNodePort);
//     threadList.push_back(dynamic_cast<module *>(sender));
//     threadList.push_back(dynamic_cast<module *>(recver));

//     return true;
// }

// void FW_run()
// {
//     for (auto _thread : threadList)
//     {
//         _thread->start();
//     }
//     while (1)
//     {
//         sleep(1);
//     }
// }
