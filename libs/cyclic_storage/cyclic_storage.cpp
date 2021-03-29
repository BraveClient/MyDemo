/**
 * @file cyclic_storage.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "cyclic_storage.hpp"

using namespace std;

cyclic_storage::cyclic_storage(std::string rootPath, uint64_t maxLarge, EN_cyclicType cyclicType, uint32_t countMax)
{
    init(rootPath, maxLarge, cyclicType, countMax);
}

cyclic_storage::~cyclic_storage()
{
}

void cyclic_storage::init(string rootPath, uint64_t maxLarge, EN_cyclicType cyclicType, uint32_t countMax)

{
    string lastFileName;
    string numstr;

    _rootPath = rootPath;
    _cyclicType = cyclicType;

    _countMax = countMax;
    _maxLarge = maxLarge;

    if (!dirExist(rootPath))
    {
        deletefiles(_rootPath);
        mkPath(_rootPath);
    }

    _usedLarge = getDirSize(_rootPath);
    getSubFileList();
    if (_fileList.size() <= 0)
    {
        _countNow = 0;
    }
    else
    {
        _countNow = findCountMax();

        while (_usedLarge > _maxLarge && _fileList.size() > 0)
        {
            deletefiles(_fileList.back());
            _fileList.pop_back();
        }
    }
}

int cyclic_storage::deletefiles(string path)
{
    //to do
    struct stat filestat;
    int ret = 0;

    if (-1 == lstat(path.c_str(), &filestat))
    {
        return -1;
    }
    if (S_ISREG(filestat.st_mode))
    {
        if (remove(path.c_str()) == -1)
        {
            return -1;
        }
    }
    else if (S_ISDIR(filestat.st_mode))
    {
        DIR *dirp = opendir(path.c_str());
        if (!dirp)
        {
            return -1;
        }
        struct dirent *dir;
        struct stat st;
        while ((dir = readdir(dirp)) != NULL)
        {
            if ("." == string(dir->d_name) || ".." == string(dir->d_name))
            {
                continue;
            }

            string sub_path = path + '/' + dir->d_name;
            if (0 != deletefiles(sub_path))
            {
                return -1;
            }
        }

        if (remove(path.c_str()) == -1) //delete dir itself.
        {
            closedir(dirp);
            return -1;
        }
        closedir(dirp);
        return 0;
    }
    return 0;
}

uint64_t cyclic_storage::getDirSize(string dirPath)
{
    struct stat filestat;
    int ret = 0;
    uint64_t size = 0;
    DIR *pDir;
    struct dirent *pDirent;
    ret = stat(dirPath.c_str(), &filestat);

    if (0 != ret)
    {
        cout << "ret = " << ret << " fileName = " << dirPath << endl;
        return 0;
    }
    size = filestat.st_size;

    if (filestat.st_mode & S_IFDIR)
    {
        pDir = opendir(dirPath.data());
        if (!pDir)
        {
            fprintf(stderr, "open directory error,%x,%x,%x\n", filestat.st_mode, S_IFDIR, filestat.st_mode | S_IFDIR);
            return 0;
        }
        while (pDirent = readdir(pDir))
        {
            // string dirname(pDirent->d_name);
            // string dirname0 =string(pDirent->d_name);
            // cout<< dirname<<" "<<dirname0<<endl;
            if ("." == string(pDirent->d_name) || ".." == string(pDirent->d_name))
            {
                continue;
            }

            string subPath = dirPath + "/" + string(pDirent->d_name);
            size += getDirSize(subPath);
        }
        closedir(pDir);
        return size;
    }
    else
    {
        return size;
    }
}

string cyclic_storage::getNextFileName()
{
    char temp[40] = {};
    int fileNameLength = 0;

    _countNow += 1;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    fileNameLength = std::snprintf(temp, 40, "%04d_%04d%02d%02d_%02d%02d%02d", _countNow,
                                   ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday,
                                   ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

    _fileNameNow = string(temp, 20);

    return _fileNameNow;
}

string cyclic_storage::getFileAbsuluatePathNext()
{
    _absuluateFileNameNow = _rootPath + "/" + getNextFileName();

    switch (_cyclicType)
    {
    case EN_cyclicType::CYCLIC_TYPE_DIR:
        mkPath(_absuluateFileNameNow);
        break;
    case EN_cyclicType::CYCLIC_TYPE_FILE:
    default:
        break;
    }
    return _absuluateFileNameNow;
}
string cyclic_storage::getFileAbsuluatePathNow()
{
    return _absuluateFileNameNow;
}

string cyclic_storage::getNowFileName()
{
    return _fileNameNow;
}

uint64_t cyclic_storage::maxLarge()
{
    return _maxLarge;
}

uint64_t cyclic_storage::usedLarge()
{
    return _usedLarge;
}

EN_cyclicType cyclic_storage::cyclicType()
{
    return _cyclicType;
}

bool cyclic_storage::getSubFileList()
{
    DIR *pDir;
    struct dirent *filename;

    _fileList.clear();

    pDir = opendir(_rootPath.data());
    if (!pDir)
    {
        fprintf(stderr, "open directory error\n");
        return false;
    }
    while (filename = readdir(pDir))
    {
        if ("." == string(filename->d_name) || ".." == string(filename->d_name))
        {
            continue;
        }
        _fileList.push_back(string(filename->d_name));
    }
    closedir(pDir);

    _fileList.sort();

    return true;
}

bool cyclic_storage::dirExist(string path)
{
    struct stat dirStat;
    if (0 != lstat(path.c_str(), &dirStat))
    {
        return false;
    }
    if (dirStat.st_mode & S_IFDIR)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int cyclic_storage::mkPath(string path)
{
    if ("/" == path || dirExist(path))
    {
        return SUCCESS;
    }
    int ret;

    string pathWithoutSlant = path;
    if ('/' == pathWithoutSlant.back())
    {
        pathWithoutSlant.pop_back();
    }
    size_t pos = pathWithoutSlant.find_last_of("/");
    string prePath = pathWithoutSlant.substr(0, pos); //上级目录

    if (dirExist(prePath))
    {
        if (0 != mkdir(pathWithoutSlant.c_str(), S_IRWXU | S_IRWXG | S_IRWXO))
        {
            cout << "make dir failure" << pathWithoutSlant << endl;
            return FAILURE;
        }
    }
    else
    {
        if (!mkPath(prePath))
        {
            cout << "make dir failure" << prePath << endl;
            return FAILURE;
        }
    }

    return SUCCESS;
}

int cyclic_storage::resizeSaveLarge(uint64_t newLarge, uint32_t newCountMax)
{
    int ret = FAILURE;
    if (newLarge < SIZE_1M)
    {
        return FAILURE;
    }
    for (int i = 0; i < newCountMax; i++)
    {
        if (_usedLarge < newLarge)
        {
            ret = SUCCESS;
            break;
        }
        if (_fileList.size() <= 0)
        {
            ret = FAILURE;
            break;
        }
        else
        {
            deletefiles(_fileList.front());
            _fileList.pop_front();
        }
    }
    return ret;
}
int cyclic_storage::resizeSaveLarge(uint64_t newLarge)
{
    return resizeSaveLarge(newLarge, _countMax);
}
int cyclic_storage::resizeSaveLarge(uint32_t _countMax)
{
    return resizeSaveLarge(_maxLarge, _countMax);
}
int cyclic_storage::resizeSaveLarge()
{
    return resizeSaveLarge(_maxLarge, _countMax);
}
uint32_t cyclic_storage::findCountMax()
{
    uint32_t count = 0;

    while (!_fileList.empty())
    {
        std::string lastFileName = _fileList.back();
        try
        {
            count = std::stoi(lastFileName);
        }
        catch (std::invalid_argument &) // 若不能进行转换则为 std::invalid_argument
        {
            deletefiles(lastFileName);
            _fileList.pop_back();
            log_debug("Invalid_argument,fileName = %s",lastFileName.c_str());
            continue;
        }
        catch (std::out_of_range &) // 若转换值会落在结果类型的范围外，或若底层函数（ std::strtol 或 std::strtoll ）设置 errno 为 ERANGE 则为 std::out_of_r
        {
            deletefiles(lastFileName);
            _fileList.pop_back();
            log_debug("Out of range,fileName = %s",lastFileName.c_str());
            continue;
        }
        catch (...)
        {
            deletefiles(lastFileName);
            _fileList.pop_back();
            log_debug("Something else,fileName = %s",lastFileName.c_str());
            continue;
        }
        break;
    }

    return count;
}