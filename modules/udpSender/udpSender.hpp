/**
 * @file udpSender.hpp
 * @author yh(forgetsky001@qq.com)
 * @brief udp数据发送线程
 * @version 0.1
 * @date 2020-12-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#define UDP_RECV_MESSAGE_LENGTH_MAX (1400)
#define UDP_RECV_PORTS_MAX (16)

#include "../../include/defines.h"
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <string.h>
#include "../../include/module.h"
#include <sys/socket.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <poll.h>
#include <memory>
#include "../../include/containers/AbstructThreadsafeMethod.hpp"
#include "../../modules/logger/logger.hpp"

class udpSender : public module
{
public:
	udpSender();
	udpSender(AbstructThreadsafeMethod<ST_UDP_DATA>* pSendQueue,std::string localIP = "0.0.0.0", uint16_t port=0);
	~udpSender();
	bool init(std::string localIP, uint16_t port);

	void run() override;

	void getCommunicateQueue(AbstructThreadsafeMethod<ST_UDP_DATA> *dataqueue);
	bool setCommunicateQueue(AbstructThreadsafeMethod<ST_UDP_DATA> *dataqueue);

private:
	AbstructThreadsafeMethod<ST_UDP_DATA> *_pSendQueue=nullptr;
	// ThreadsafeQueue<ST_UDP_DATA,1024> _sendBuf;
	std::string _localip="0.0.0.0";
	int _udpSnedFd=-1;
	uint16_t _port=0;
};