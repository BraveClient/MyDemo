/**
 * @file cyclic_storage.hpp
 * @author yh(forgetsky001@qq.com)
 * @brief 检测文件夹大小和已存在的文件，在规定大小下循环存储
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <regex>
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <stdint.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <error.h>
#include "../../include/defines.h"
#include "../../include/version.h"
#include "../../modules/logger/logger.hpp"

const uint64_t SIZE_1K = 1024ll;
const uint64_t SIZE_1M = SIZE_1K * 1024ll;
const uint64_t SIZE_1G = SIZE_1M * 1024ll;
const uint64_t SIZE_1T = SIZE_1G * 1024ll;

enum class EN_cyclicType
{
    CYCLIC_TYPE_DIR,
    CYCLIC_TYPE_FILE
};

class cyclic_storage
{
private:
    std::string _rootPath;
    EN_cyclicType _cyclicType;
    std::list<std::string> _fileList;
    uint32_t _countMax;
    std::string _fileNameNow;
    std::string _absuluateFileNameNow;
    uint32_t _countNow;
    uint64_t _usedLarge;
    uint64_t _maxLarge;

    int deletefiles(std::string path);
    uint64_t getDirSize(std::string dirPath);
    bool getSubFileList();
    bool dirExist(std::string path);
    int mkPath(std::string path);
    uint32_t findCountMax();

public:
    cyclic_storage(std::string rootPath, uint64_t maxLarge = SIZE_1T, EN_cyclicType cyclicType = EN_cyclicType::CYCLIC_TYPE_DIR, uint32_t countMax = 10000);
    ~cyclic_storage();
    void init(std::string rootPath, uint64_t maxLarge, EN_cyclicType cyclicType, uint32_t countMax);
    std::string getNextFileName();
    std::string getNowFileName();
    uint64_t maxLarge();
    uint64_t usedLarge();
    EN_cyclicType cyclicType();
    int resizeSaveLarge(uint64_t newLarge, uint32_t _countMax);
    int resizeSaveLarge(uint64_t newLarge);
    int resizeSaveLarge(uint32_t _countMax);
    int resizeSaveLarge();
    std::string getFileAbsuluatePathNext();
    std::string getFileAbsuluatePathNow();
};
