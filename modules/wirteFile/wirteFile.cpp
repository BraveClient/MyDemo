/**
 * @file wirteFile.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "wirteFile.hpp"
using namespace std;

wirteFile::wirteFile(AbstructThreadsafeMethod<ST_UDP_DATA> *pDataQueue) : _pDataQueue(pDataQueue),
                                                                          cyclic_storage(SAVE_PATH_1, SIZE_1M * 100)
{
}

wirteFile::~wirteFile()
{
}

void wirteFile::run()
{
    std::string infoSysDataPath;
    std::string firstPack;
    std::string timePack;

    infoSysDataPath = getFileAbsuluatePathNext();
    if (infoSysDataPath.empty())
    {
        //TODO log
        // cout << LOG_ERR << "-[" << __FILE__ << ":" << __LINE__ << "]"
        //      << "get Empty file path." << endl;
        goto EXIT0_NO_SAVEPATH;
    }

    infoSysDataPath += string("/INFO_SYS.dat");
    _infoSysDataFile.open(infoSysDataPath, ios::binary | ios::out | ios::trunc);

    if (!_infoSysDataFile.is_open())
    {
        goto EXIT1_OPEN_FILE_FAILURE;
    }

    log_info("data record file name:%s",infoSysDataPath.c_str());

    // DataStoragePack::packFirst(firstPack);
    // DataStoragePack::packTime(timePack);
    if (SUCCESS != writeStringToFile(firstPack) || SUCCESS != writeStringToFile(timePack))
    {
        goto EXIT2_WRITE_FILE_ERROR;
        return;
    }

    log_trace("---------------------------thread start-------------------------------");

    while (_runSta)
    {
        ST_UDP_DATA recvData;
        _pDataQueue->waitPop(recvData);
        if (SUCCESS != packDataToFile(recvData))
        {
            break;
        }

        while (_pDataQueue->tryPop(recvData))
        {
            if (SUCCESS != packDataToFile(recvData))
            {
                break;
            }
        }
    }

EXIT2_WRITE_FILE_ERROR:
    _infoSysDataFile.close();
EXIT1_OPEN_FILE_FAILURE:
    _infoSysDataFile.clear();
EXIT0_NO_SAVEPATH:
    _runSta = false;
    return;
}

int wirteFile::packDataToFile(ST_UDP_DATA &data)
{
    string destData;
    // DataStoragePack::packData(destData, data.data);
    packData(destData, data.data);
    return writeStringToFile(destData);
}

bool wirteFile::packData(std::string &dest, const std::string &src)
{
    Net_Frame_Info_Header header;
    int data;
    uint16_t sum = 0;

    time_t t = time(NULL);
    struct tm *lt = localtime(&t);

    struct timespec time1 = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &time1);

    header.channel1 = 0xEA;
    //通道标识符2
    header.channel2 = 0xEA;
    //本帧字节数
    header.frame_len = sizeof(Net_Frame_Info_Header) + src.size() + sizeof(sum);
    //源标识符
    header.src_id = 0;
    //目的标识符
    header.dest_id = 0;
    //日期
    header.date = (lt->tm_year + 1900) * 10000 + (lt->tm_mon + 1) * 100 + (lt->tm_mday);
    //绝对时间
    header.absolute_time = (lt->tm_hour) * 10000 + lt->tm_min * 100 + lt->tm_sec;
    //相对时间
    header.relative_time = time1.tv_sec * 1000 + time1.tv_nsec / 1000;
    //本帧包含域个数
    header.attach_yu_num = 1;

    dest.clear();
    dest = std::string((char *)&header, sizeof(header)) + src;

    for (auto c : dest)
    {
        sum += c;
    }
    dest += std::string((char *)&sum, sizeof(sum));

    return true;
}

int wirteFile::writeStringToFile(std::string &data)
{
    int ret = FAILURE;

    try
    {
        _infoSysDataFile.write(data.c_str(), data.size());
        ret = SUCCESS;
    }
    catch (const std::exception &e)
    {
        ret = FAILURE;

        //TODO:log
        std::cerr << e.what() << '\n';
    }

    return ret;
}