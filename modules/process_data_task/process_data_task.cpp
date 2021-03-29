
#include "process_data_task.hpp"
using namespace std;

Process_data_task *Process_data_task::_pInstance = new Process_data_task();

Process_data_task::Process_data_task()
{
}

Process_data_task::~Process_data_task()
{
}

void Process_data_task::run()
{
    log_trace("---------------------------thread start-------------------------------");
    while (_runSta)
    {
        ST_UDP_DATA udpDatabuf;
        _pUdpRecvDataQueue->waitPop(udpDatabuf);
        //do something
        while (_pUdpRecvDataQueue->tryPop(udpDatabuf))
        {
            //do something
        }
    }
}

void Process_data_task::processData(ST_UDP_DATA& udpDatabuf)
{
    
}