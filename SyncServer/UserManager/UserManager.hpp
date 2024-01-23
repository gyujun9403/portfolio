#pragma once

#include "../pch.hpp"

#define MAX_CLIENT_DELAY 0.03

struct UserStatus
{
    std::chrono::system_clock::time_point  reservedTime;
    std::pair<float, float> loc;
    std::pair<float, float> vel;

    UserStatus()
    {
        reservedTime = std::chrono::system_clock::now();
        loc = std::make_pair(0, 0);
        vel = std::make_pair(0, 0);
    }

    UserStatus(float locX, float locY, float velX, float velY, float sendDelaySec, float recvDelaySec)
    {
        float sendApplyDelay = (sendDelaySec + recvDelaySec < MAX_CLIENT_DELAY) ? (sendDelaySec + recvDelaySec) : (MAX_CLIENT_DELAY);
        float caledDelay = (sendApplyDelay - sendDelaySec + recvDelaySec) / 2;
        float delaySec = (caledDelay > 0) ? (caledDelay) : (0);
        auto nowTime = std::chrono::system_clock::now();
        // 컨트롤 예약 적용
        reservedTime = nowTime + std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::duration<float>(delaySec));
        // 컨트롤 바로 적용
        //reservedTime = nowTime;
        loc.first = locX; loc.second = locY; 
    }
};

class UserManager
{
public:
    UserManager();
    ~UserManager();
    void ReserveStatus(UserStatus status);
    void DoLogging();
    void StopLogging();
    
private:
    const std::string FILE_NAME_PREFIX = "ServerLog";
    char _timeStrBuffer[24];

    std::atomic<bool> _isRunning;
    std::atomic<bool> _isLogging;
    std::deque<UserStatus> _reservedStatus;
    
    std::mutex _inputStatusMutex;
    std::queue<UserStatus> _inputStatusQueue;
    std::thread _userStatusThread;
    UserStatus _nowStatus;
    std::ofstream _loggingStream;
    std::chrono::system_clock::time_point _nextLoggineTime;

    std::optional<UserStatus> PopStatus();
    void RenewalStatus();
    void renewalTimeBuf();
    void PrintStatusLog();
};