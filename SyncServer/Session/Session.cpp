#include "Session.hpp"

Session::Session(int fd)
: _fd(fd)
{}

std::pair<BuffVec*, int> Session::recv()
{
    int recvByte = ::recv(_fd, &_recvBuf, MAX_BUF_SIZE, 0);
    if (recvByte < 0)
    {
        if (errno != EWOULDBLOCK)
        {
            std::cerr << _fd << " client recv fail" << std::endl;
            return std::make_pair(nullptr, recvByte);
        }
        return std::make_pair(&_recvBuf, recvByte);
    }
    else if (recvByte == 0)
    {
        std::cout << _fd << " client out" << std::endl;
        return std::make_pair(&_recvBuf, recvByte);
    }
    else
    {
        return std::make_pair(&_recvBuf, recvByte);
    }
}

int Session::send(BuffVec&& sendData, int sendSize)
{
    _SendBuf = sendData;
    int sendByte = ::send(_fd, &_SendBuf, sendSize, 0);
    if (sendByte < 0)
    {
        if (errno != EWOULDBLOCK)
        {
            std::cerr << _fd << " client send fail" << std::endl;
            return false;
        }
        std::cerr << _fd << " would block" << std::endl;
        return true;
    }
    else
    {
        if (sendByte < sendSize)
        {
            std::cerr << _fd << " client send partilally" << std::endl;
        }
    }
    return true;
}