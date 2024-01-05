#include <thread>
#include <cerrno>


#include "Server.hpp"

Server::Server(int port, int maxClinetNum)
: _PORT_NUM(port), _MAX_CLIENT_NUM(maxClinetNum)
{
    _epollEvents = std::make_unique<struct epoll_event[]>(maxClinetNum);
    
}

bool Server::initServer()
{
    _serverAddr.sin_family = AF_INET;;
    _serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    _serverAddr.sin_port = htons(_PORT_NUM);

    _serverSockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSockFd < 0)
    {
        std::cerr << "socket Error :" << _serverSockFd << ',' << errno << std::endl;
        return false; 
    }
    return true;
}

bool Server::RunServer()
{
    int rt = bind(_serverSockFd, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr));
    if (rt < 0)
    {
        std::cerr << "bind fail:" << rt << ',' << errno  << std::endl;
        return false;
    }

    rt = listen(_serverSockFd, 4);
    if (rt < 0)
    {
        std::cerr << "listen fail:" << rt << ',' << errno << std::endl;
        return false;
    }

    int epollFd = epoll_create1(0);
    if (epollFd < 0)
    {
        std::cerr << "epoll_create1 fail:" << epollFd << ',' << errno << std::endl;
        return false;
    }
    _epollEvents = std::make_unique<epoll_event[]>(_MAX_CLIENT_NUM);


    int occurEventNum = epoll_wait(epollFd, _epollEvents.get(), _MAX_CLIENT_NUM, -1);
    for (int i = 0; i < occurEventNum; i++)
    {
        if (_epollEvents[i].data.fd == _serverSockFd)
        {
            socklen_t clientAddrLen = sizeof(_serverAddr);
            int clientSockFd = accept(_serverSockFd, (sockaddr*)&_serverAddr, &clientAddrLen);
            if (clientSockFd < 0)
            {
                std::cerr << clientSockFd << ',' << errno << std::endl;
                continue;
            }

            epoll_event clientEvent;
            clientEvent.events = EPOLLIN | EPOLLET;
            clientEvent.data.fd = clientSockFd;
            rt = epoll_ctl(epollFd, EPOLL_CTL_ADD, clientSockFd, &clientEvent);
            if (rt < 0)
            {
                std::cerr << rt << ',' << errno << std::endl;
                continue;
            }
            std::cout << "accept" << std::endl;
        }
        else
        {
            std::cout << "else" << std::endl;
        }
    }
    return true;

}