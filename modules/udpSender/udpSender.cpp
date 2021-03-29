/**
 * @file udpSender.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "udpSender.hpp"

udpSender::udpSender()
{
}
udpSender::udpSender(AbstructThreadsafeMethod<ST_UDP_DATA> *pSendQueue, std::string localIP, uint16_t port)
{
	_pSendQueue = pSendQueue;
	_port = port;
	_localip = localIP;
}
udpSender::~udpSender()
{
}
bool udpSender::init(std::string localIP, uint16_t port)
{
	_port = port;
	_localip = localIP;
	return true;
}

void udpSender::run()
{
	int ret = 0;
	struct sockaddr_in sendAddr;

	bzero(&sendAddr, sizeof(struct sockaddr_in));
	sendAddr.sin_family = AF_INET;
	if (_localip.empty())
	{
		sendAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		sendAddr.sin_addr.s_addr = inet_addr(_localip.c_str());
	}
	sendAddr.sin_port = htons(_port);

	_udpSnedFd = socket(AF_INET, SOCK_DGRAM, 0); //UDP
	if (-1 == _udpSnedFd)
	{
		_runSta = false;
		return;
	}

	ret = bind(_udpSnedFd, (struct sockaddr *)&sendAddr, sizeof(struct sockaddr));
	if (0 != ret)
	{
		_runSta = false;
		return;
	}

	if (nullptr == _pSendQueue)
	{
		_runSta = false;
		return;
	}
	log_trace("---------------------------thread start-------------------------------");
	while (_runSta)
	{
		ST_UDP_DATA sendData;
		_pSendQueue->waitPop(sendData);

		struct sockaddr_in dest;
		bzero(&dest, sizeof(struct sockaddr_in));
		dest.sin_family = AF_INET;
		dest.sin_addr.s_addr = inet_addr(sendData.desIP.c_str());
		dest.sin_port = htons(sendData.desPort);
		sendto(_udpSnedFd, sendData.data.c_str(), sendData.data.size(), 0, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));

		while (_pSendQueue->tryPop(sendData))
		{
			bzero(&dest, sizeof(struct sockaddr_in));
			dest.sin_family = AF_INET;
			dest.sin_addr.s_addr = inet_addr(sendData.desIP.c_str());
			dest.sin_port = htons(sendData.desPort);
			sendto(_udpSnedFd, sendData.data.c_str(), sendData.data.size(), 0, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
		}
	}
	_runSta = false;
}

void udpSender::getCommunicateQueue(AbstructThreadsafeMethod<ST_UDP_DATA> *dataqueue)
{
	dataqueue = _pSendQueue;
}
bool udpSender::setCommunicateQueue(AbstructThreadsafeMethod<ST_UDP_DATA> *dataqueue)
{
	if (true == _runSta)
	{
		return false;
	}

	if (!_pSendQueue)
	{
		delete _pSendQueue;
		_pSendQueue = nullptr;
	}

	_pSendQueue = dataqueue;
	return true;
}