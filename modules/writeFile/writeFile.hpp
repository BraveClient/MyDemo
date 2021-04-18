/**
 * @file writeFile.hpp
 * @author yh(forgetsky001@qq.com)
 * @brief 写数据到硬盘
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <string>
#include <fstream>
#include "../../include/module.h"
#include "../../include/defines.h"
#include "../../libs/cyclic_storage/cyclic_storage.hpp"
#include "../../libs/dataStorePack/dataStorePack.hpp"
#include "../../include/containers/AbstructThreadsafeMethod.hpp"
#include "../../modules/logger/logger.hpp"

const std::string SAVE_PATH = "/home/pi/Documents/DataRecorder/DATA/";
#define SAVE_PATH_1 "/home/pi/Documents/DataRecorder/DATA/"

const uint32_t MAX_COUNT = 10000;
const uint64_t MAX_SIZE = 5 * SIZE_1G;



class writeFile : public module, private cyclic_storage
{
private:
	AbstructThreadsafeMethod<ST_UDP_DATA> *_pDataQueue{nullptr};
	std::ofstream _infoSysDataFile;
	int writeStringToFile(std::string &data);
	int packDataToFile(ST_UDP_DATA &data);
	bool packData(std::string &dest,const std::string& src);
public:
private:
	void run() override;

public:
	writeFile(AbstructThreadsafeMethod<ST_UDP_DATA> *pDataQueue);
	~writeFile();
};
