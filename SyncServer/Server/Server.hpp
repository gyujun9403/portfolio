#pragma once

#include "../Session/SessionContainer.hpp"
#include "../PacketProcesser/PacketProcesser.hpp"

#define THREAD_NUM 4
#define LISTEN_QUEUED_REQ 4

class Server
{
public:
    Server(int port, int maxClinetNum);
    bool initServer();
    bool RunServer();
    bool ServerSockProcesses(); // Accept
    bool ClientSockProcesses(const epoll_event& event);
    ~Server();
private:
    SessionContainer _sessionContainer;

    const int _PORT_NUM;
    const int _MAX_CLIENT_NUM;
    int _epollFd;
    int _serverSockFd;
    sockaddr_in _serverAddr;
    PacketProcesser _processer;

    std::unique_ptr<struct epoll_event[]> _epollEvents;
    std::string getCurrentTimeFormatted();
};