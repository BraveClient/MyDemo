/**
 * @file udpReceiver.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

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
#include "../../include/containers/AbstructThreadsafeMethod.hpp"
#include "../../include/defines.h"
#include "../../modules/logger/logger.hpp"

#define UDP_RECV_MESSAGE_LENGTH_MAX (1400)
#define UDP_RECV_PORTS_MAX (16)

class udpReceiver : public module
{
public:
	udpReceiver();
	udpReceiver(AbstructThreadsafeMethod<ST_UDP_DATA>* pSendQueue,AbstructThreadsafeMethod<ST_UDP_DATA>* pDataQueue,
				std::string localIP = "0.0.0.0", uint16_t port=65000u);
	// udpReceiver(AbstructThreadsafeMethod<ST_UDP_DATA>* pSendQueue,AbstructThreadsafeMethod<ST_UDP_DATA>* pDataQueue);
	udpReceiver(std::string localIP, std::vector<uint16_t> portList);
	~udpReceiver();
	bool init(std::string localIP, std::vector<uint16_t> portList);

	void  run() override;
private:
	AbstructThreadsafeMethod<ST_UDP_DATA>* _pRecvQueue{nullptr};
	AbstructThreadsafeMethod<ST_UDP_DATA>* _pDataQueue{nullptr};

	std::string _localIP;
	std::vector<uint16_t> _ports;
	struct sockaddr_in _recvAddr[UDP_RECV_PORTS_MAX];
	int _udpRecvFd[UDP_RECV_PORTS_MAX] = {0};
	struct pollfd _pollfds[UDP_RECV_PORTS_MAX]; //监测文件描述结构体数组
	uint32_t _fdsSize=0;
};