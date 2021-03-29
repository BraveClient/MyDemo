/**
 * @file udpReceiver.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "udpReceiver.hpp"

udpReceiver::udpReceiver()
{
}
udpReceiver::udpReceiver(AbstructThreadsafeMethod<ST_UDP_DATA> *pRecvQueue,
						 AbstructThreadsafeMethod<ST_UDP_DATA> *pDataQueue,
						 std::string localIP, uint16_t port)
{
	_pRecvQueue = pRecvQueue;
	_pDataQueue = pDataQueue;
	_localIP = localIP;
	_ports.resize(1);
	_ports[0] = port;
}
udpReceiver::udpReceiver(std::string localIP, std::vector<uint16_t> portList)
{
	_ports = portList;
	_localIP = localIP;
}
udpReceiver::~udpReceiver()
{
}
bool udpReceiver::init(std::string localIP, std::vector<uint16_t> portList)
{
	if (true == _runSta || portList.size() > UDP_RECV_PORTS_MAX)
	{
		return false;
	}
	else
	{
		_ports = portList;
		_localIP = localIP;
		return true;
	}
}

void udpReceiver::run()
{
	int ret = 0;
	char pRecvBuf[UDP_RECV_MESSAGE_LENGTH_MAX];
	size_t recvLengh = 0;

	_fdsSize = _ports.size();
	if (_fdsSize < 0)
	{
		_runSta = false;
		return;
	}

	// char *localIP = const_cast<char *>(_localIP.c_str());
	for (int i = 0; i < _ports.size() && (i < UDP_RECV_PORTS_MAX); i++)
	{

		bzero(&_recvAddr[i], sizeof(struct sockaddr_in));
		_recvAddr[i].sin_family = AF_INET;
		// recvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		_recvAddr[i].sin_addr.s_addr = inet_addr(_localIP.c_str());
		_recvAddr[i].sin_port = htons(_ports.at(i));

		_udpRecvFd[i] = socket(AF_INET, SOCK_DGRAM, 0); //UDP
		if (-1 == _udpRecvFd[i])
		{
			_runSta = false;
			return;
		}

		ret = bind(_udpRecvFd[i], (struct sockaddr *)&_recvAddr[i], sizeof(struct sockaddr));
		if (0 != ret)
		{
			perror("bind");
			_runSta = false;
			return;
		}
		log_trace("recvThred bind ip&port: %s:%d",_localIP.c_str(),_ports.at(i));

		_pollfds[i].fd = _udpRecvFd[i]; //udp描述符
		_pollfds[i].events = POLLIN;	// 普通或优先级带数据可读
	}

	ST_UDP_DATA *pData = new ST_UDP_DATA;

	log_trace("---------------------------thread run-------------------------------");
	while (_runSta)
	{
		// 监视并等待多个文件（标准输入，udp套接字）描述符的属性变化（是否可读）
		// 没有属性变化，这个函数会阻塞，直到有变化才往下执行，这里没有设置超时
		ret = poll(_pollfds, _fdsSize, -1);

		if (ret == -1)
		{ // 出错
			perror("poll()");
		}
		else if (ret > 0)
		{
			for (int i = 0; i < _fdsSize; i++)
			{
				if ((_pollfds[i].revents & POLLIN) == POLLIN)
				{
					struct sockaddr_in addr;
					char ipbuf[INET_ADDRSTRLEN] = "";
					socklen_t addrlen = sizeof(addr);

					bzero(&addr, sizeof(addr));

					recvLengh = recvfrom(_udpRecvFd[i], pRecvBuf, UDP_RECV_MESSAGE_LENGTH_MAX, 0, (struct sockaddr *)&addr, &addrlen);

					pData->srcIP = std::string(inet_ntoa(addr.sin_addr));
					pData->srcPort = ntohs(addr.sin_port);
					pData->desIP = _localIP;
					pData->desPort = _ports[i];
					pData->data = std::string(pRecvBuf, recvLengh);

					_pRecvQueue->tryPush(*pData);
					_pDataQueue->tryPush(*pData);

				}
			}
		}
	}
	delete pData;
	_runSta = false;
}