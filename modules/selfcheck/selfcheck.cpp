
#include "selfcheck.hpp"
using namespace std;

Selfcheck *Selfcheck::_pInstance = new Selfcheck();

Selfcheck::Selfcheck()
{
}

Selfcheck::~Selfcheck()
{
}

bool Selfcheck::init(AbstructThreadsafeMethod<ST_UDP_DATA>* udpRecvDataQueue)
{
    _pUdpRecvDataQueue = udpRecvDataQueue;
    return true;
}

void Selfcheck::run()
{
    log_trace("---------------------------thread start-------------------------------");
    GlobalData *globaleData = GlobalData::getInstance();
    std::string dataServerIP = globaleData->getNode("USDataServer").at("ip");
    uint16_t dataServerPort = globaleData->getNode("USDataServer").at("port");

    ST_UDP_DATA selfcheckSendData;
    selfcheckSendData.desIP = dataServerIP;
    selfcheckSendData.desPort = dataServerPort;

    log_trace("---------------------------thread run-------------------------------");
    while (_runSta)
    {
        _pUdpRecvDataQueue->tryPush(selfcheckSendData);
        sleep(1);
    }
}