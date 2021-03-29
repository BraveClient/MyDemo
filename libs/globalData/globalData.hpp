/**
 * @file globalData.hpp
 * @author yh(forgetsky001@qq.com)
 * @brief 全局变量 单例模式 饿汉
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once
#include "../../include/defines.h"
#include "../../include/containers/AbstructThreadsafeMethod.hpp"
#include "../../include/containers/ThreadsafeQueue.hpp"
#include "../../include/containers/ThreadsafeRingBuffer.hpp"
#include "../../include/json.hpp"
#include "pthread.h"
#include <string>

class GlobalData
{
private:
    GlobalData();
    GlobalData(const GlobalData &) = delete;
    GlobalData &operator=(const GlobalData &) = delete;
    ~GlobalData();
    static GlobalData *_pInstance;

    AbstructThreadsafeMethod<ST_UDP_DATA> *_pUdpSendQueue{nullptr};     //udp发送数据通信
    AbstructThreadsafeMethod<ST_UDP_DATA> *_pUdpRecvSaveQueue{nullptr}; //udp for save 
    AbstructThreadsafeMethod<ST_UDP_DATA> *_pUdpRecvDataQueue{nullptr}; //udp for despose
    AbstructThreadsafeMethod<std::string> *_pLogDataQueue{nullptr}; //log

    nlohmann::json _masterNodes;

    // nlohmann::json _dataRecorderNode;
    // nlohmann::json _dataServerNode;

    
public:
    static GlobalData *getInstance() { return _pInstance; }
    AbstructThreadsafeMethod<ST_UDP_DATA> *getUdpSendQueue() { return _pUdpSendQueue; }
    AbstructThreadsafeMethod<ST_UDP_DATA> *getUdpRecvSaveQueue() { return _pUdpRecvSaveQueue; }
    AbstructThreadsafeMethod<ST_UDP_DATA> *getUdpRecvDataQueue() { return _pUdpRecvDataQueue; }
    AbstructThreadsafeMethod<std::string> *getLogDataQueue() { return _pLogDataQueue; }

    bool setMasterNode(nlohmann::json nodes);
    nlohmann::json getNode(const std::string nodeName );
    pthread_rwlock_t _rwlocker_Nodes = PTHREAD_RWLOCK_INITIALIZER;

};