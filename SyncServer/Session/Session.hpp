#pragma once
#include "../pch.hpp"


class Session
{
public:
    Session(int fd);
    std::pair<BuffVec*, int> recv();
    int send(BuffVec&& sendData, int sendSize);
private:
    int _fd;
    BuffVec _recvBuf;
    BuffVec _SendBuf;
};