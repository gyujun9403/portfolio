#include "SessionContainer.hpp"

Session* SessionContainer::FindSession(int fd)
{
    auto iter = _sessionMap.find(fd);
    if (iter == _sessionMap.end())
    {
        return nullptr;
    }
    return &iter->second;
}

bool SessionContainer::SetSession(int fd)
{
    auto iter = _sessionMap.find(fd);
    if (iter != _sessionMap.end())
    {
        return false;
    }

    _sessionMap.insert(std::make_pair(fd, Session(fd)));
    return true;
}

void SessionContainer::ClearSession(int fd)
{
    _sessionMap.erase(fd);
}