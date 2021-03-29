/**
 * @file globalData.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "globalData.hpp"

GlobalData *GlobalData::_pInstance = new GlobalData();

GlobalData::GlobalData()
{
    _pUdpSendQueue = new ThreadsafeQueue<ST_UDP_DATA, 1024>;
    _pUdpRecvSaveQueue = new ThreadsafeRingbuffer<ST_UDP_DATA, 1024>;
    _pUdpRecvDataQueue = new ThreadsafeRingbuffer<ST_UDP_DATA, 1024>;
    _pLogDataQueue = new ThreadsafeQueue<std::string, 1024>;
}

GlobalData::~GlobalData()
{
    delete _pUdpSendQueue;
    _pUdpSendQueue = nullptr;
    delete _pUdpRecvSaveQueue;
    _pUdpRecvSaveQueue = nullptr;
    delete _pUdpRecvDataQueue;
    _pUdpRecvDataQueue = nullptr;

}

bool GlobalData::setMasterNode(nlohmann::json nodes)
{
    pthread_rwlock_wrlock(&_rwlocker_Nodes);
    _masterNodes = nodes;
    pthread_rwlock_unlock(&_rwlocker_Nodes);
    return true;
}
nlohmann::json GlobalData::getNode(std::string nodeName)
{
    nlohmann::json node;

    pthread_rwlock_rdlock(&_rwlocker_Nodes);
    for (auto n : _masterNodes)
    {
        if (nodeName == n.at("name"))
        {
            node = n;
            break;
        }
    }
    pthread_rwlock_unlock(&_rwlocker_Nodes);
    return node;
}