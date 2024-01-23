#include "UserManager.hpp"

UserManager::UserManager()
{   
    if (_loggingStream.is_open() == true)
    {
        std::cerr << "file already opened" << std::endl;
    }
    _isLogging.store(false);
    _isRunning.store(true);
    _userStatusThread = std::thread(&UserManager::RenewalStatus, this);
}

void UserManager::ReserveStatus(UserStatus status)
{
    std::unique_lock<std::mutex> lock(_inputStatusMutex);
    _inputStatusQueue.push(status);
}

void UserManager::DoLogging()
{
    renewalTimeBuf();
    if (_loggingStream.is_open() == true)
    {
        _loggingStream.close();
    }
    std::string fileName = FILE_NAME_PREFIX + _timeStrBuffer + std::string(".txt");
    _loggingStream.open(fileName, std::ios::trunc);
    _loggingStream << "Time" << '\t' << "LocX" << std::endl;
    _isLogging.store(true);
}

void UserManager::StopLogging()
{
    if (_loggingStream.is_open() == true)
    {
        _loggingStream.close();
    }
    _isLogging.store(false);
}

std::optional<UserStatus> UserManager::PopStatus()
{
    std::optional<UserStatus> rt = std::nullopt;
    std::unique_lock<std::mutex> lock(_inputStatusMutex);
    while (_inputStatusQueue.empty() == false)
    {
        if (_inputStatusQueue.front().reservedTime <= std::chrono::system_clock::now())
        {
            rt = _inputStatusQueue.front();
            _inputStatusQueue.pop();
        }
        else
        {
            break;
        }
    }
    return rt;
}

void UserManager::RenewalStatus()
{
    while(_isRunning.load() == true)
    {
        auto rt = PopStatus();
        if (rt != std::nullopt)
        {
            _nowStatus = rt.value();
            PrintStatusLog();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void UserManager::renewalTimeBuf()
{
    auto currentTime = std::chrono::system_clock::now();
    
    auto currentTimeMillis = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();
    auto currentTimeSec = std::chrono::system_clock::to_time_t(currentTime);
    
    struct std::tm* timeinfo = std::localtime(&currentTimeSec);
    std::strftime(_timeStrBuffer, sizeof(_timeStrBuffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    std::sprintf(_timeStrBuffer + 19, ".%03ld", currentTimeMillis % 1000);
}

void UserManager::PrintStatusLog()
{
    renewalTimeBuf();
    _loggingStream << _timeStrBuffer << '\t' << _nowStatus.loc.first << std::endl;
}

UserManager::~UserManager()
{

    _isRunning.store(false);
    _userStatusThread.join();
}
