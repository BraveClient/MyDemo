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
#include "../../include/containers/AbstructThreadsafeMethod.hpp"
#include "../../include/containers/ThreadsafeQueue.hpp"
#include "../../include/containers/ThreadsafeRingBuffer.hpp"
#include <fstream>
#include <stdarg.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "../../modules/logger/logger.hpp"

class Process_data_task : public module
{
public:
    static Process_data_task *getInstance() { return _pInstance; }

private:
    Process_data_task();
    Process_data_task(const Process_data_task &) = delete;
    Process_data_task &operator=(const Process_data_task &) = delete;
    ~Process_data_task();

    void run() override;

    void processData(ST_UDP_DATA& udpDatabuf);

    static Process_data_task *_pInstance;
    AbstructThreadsafeMethod<ST_UDP_DATA> *_pUdpRecvDataQueue{nullptr};

};

