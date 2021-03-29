/**
 * @file logger.hpp
 * @author yh(forgetsky001@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

#include "../../include/common.h"
#include "../../include/module.h"
#include "../../include/defines.h"
#include "../../include/containers/AbstructThreadsafeMethod.hpp"
#include "../../include/containers/ThreadsafeQueue.hpp"
#include "../../include/containers/ThreadsafeRingBuffer.hpp"
#include "../../libs/globalData/globalData.hpp"
#include "../../libs/netProtocol/net_protocol.h"
#include "../../modules/logger/logger.hpp"
#include <fstream>
#include <stdarg.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <mutex>

class Selfcheck : public module
{
public:
    static Selfcheck *getInstance() { return _pInstance; }

    bool init(AbstructThreadsafeMethod<ST_UDP_DATA> *udpRecvDataQueue);

private:
    Selfcheck();
    Selfcheck(const Selfcheck &) = delete;
    Selfcheck &operator=(const Selfcheck &) = delete;
    ~Selfcheck();

    void run() override;

    static Selfcheck *_pInstance;
    AbstructThreadsafeMethod<ST_UDP_DATA> *_pUdpRecvDataQueue{nullptr};
};
