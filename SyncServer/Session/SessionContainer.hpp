#pragma once

#include "../pch.hpp"
#include "Session.hpp"

// 동기화 테스트용 서버 이므로, 동작만 하게 간단한기능만.
class SessionContainer
{
public:
    Session* FindSession(int fd);
    bool SetSession(int fd);
    void ClearSession(int fd);

private:
    const int MAX_SESSION_NUM = 2;

    std::map<int, Session> _sessionMap;
};