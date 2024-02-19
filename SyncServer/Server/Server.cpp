#include "../Packet/Packet.hpp"
#include "Server.hpp"

Server::Server(int port, int maxClinetNum)
: _PORT_NUM(port), _MAX_CLIENT_NUM(maxClinetNum)
{
    // +1은 accept용
    _epollEvents = std::make_unique<struct epoll_event[]>(maxClinetNum + 1);
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

    const int trueFlag = 1;
    if (setsockopt(_serverSockFd, SOL_SOCKET, SO_REUSEADDR, &trueFlag, sizeof(int)) < 0)
    {
        std::cerr << "SOL_SOCKET SO_REUSEADDR Error :" << _serverSockFd << ',' << errno << std::endl;
        return false; 
    }

    std::cout << "Server init done." << std::endl;
    return true;
}

bool Server::RunServer()
{
    epoll_event tempEvent;
    int rt = bind(_serverSockFd, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr));
    if (rt < 0)
    {
        std::cerr << "bind fail:" << rt << ',' << errno  << std::endl;
        return false;
    }
    std::cout << "Server port are binded." << std::endl;

    rt = listen(_serverSockFd, LISTEN_QUEUED_REQ);
    if (rt < 0)
    {
        std::cerr << "listen fail:" << rt << ',' << errno << std::endl;
        return false;
    }
    std::cout << "Server opened listen port" << std::endl;

    _epollFd = epoll_create1(0);
    if (_epollFd < 0)
    {
        std::cerr << "epoll_create1 fail:" << _epollFd << ',' << errno << std::endl;
        return false;
    }
    _epollEvents = std::make_unique<epoll_event[]>(_MAX_CLIENT_NUM);
    std::cout << "Server epoll event are created" << std::endl;

    tempEvent.events = EPOLLIN;
    tempEvent.data.fd = _serverSockFd;
    rt = epoll_ctl(_epollFd, EPOLL_CTL_ADD, _serverSockFd, &tempEvent);
    if (rt < 0)
    {
        std::cerr << rt << ',' << errno << std::endl;
        return -rt;
    }
    std::cout << "Server is waiting clients" << std::endl;

    while (1)
    {
        int occurEventNum = epoll_wait(_epollFd, _epollEvents.get(), _MAX_CLIENT_NUM, -1);
        for (int i = 0; i < occurEventNum; i++)
        {
            if (_epollEvents[i].data.fd == _serverSockFd)
            {
                Server::ServerSockProcesses();
            }
            else
            {
                ClientSockProcesses(_epollEvents[i]);
            }
        }
    }
    return true;

}

bool Server::ServerSockProcesses()
{
    epoll_event tempEvent;
    socklen_t clientAddrLen = sizeof(_serverAddr);

    int clientSockFd = accept(_serverSockFd, (sockaddr*)&_serverAddr, &clientAddrLen);
    if (clientSockFd < 0)
    {
        std::cerr << clientSockFd << ',' << errno << std::endl;
        return false;
    }

    int flags = fcntl(clientSockFd, F_GETFL, 0);
    if (flags == -1)
    {
        std::cerr << "fcntl(F_GETFL) error : " << errno << std::endl;
        close(clientSockFd);
        return false;
    }

    int rt = fcntl(clientSockFd, F_SETFL, flags | O_NONBLOCK);
    if (rt == -1) 
    {
        std::cerr << "fcntl(F_SETFL) error : " << errno << std::endl;
        close(clientSockFd);
        return false;
    }

    tempEvent.events = EPOLLIN | EPOLLET;
    tempEvent.data.fd = clientSockFd;
    if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, clientSockFd, &tempEvent) < 0)
    {
        std::cerr << "ServerSockProcesses epoll_ctl Error: " << errno << std::endl;
        return false;
    }

    // accept 및 소켓 설정 완료후 세션 할당 및 완료
    _sessionContainer.SetSession(clientSockFd);
    _processer.StartStatusLogging();
    std::cout << clientSockFd << " user accepted" << std::endl;
    
    return true;
}

bool Server::ClientSockProcesses(const epoll_event& event)
{
    Session* session = _sessionContainer.FindSession(event.data.fd);
    if (session == nullptr)
    {
        std::cerr << "cant find session" << std::endl;
        return false;
    }

    if (event.events & EPOLLIN)
    {
        auto received = session->recv();
        // 접속 해제
        if (received.second == 0)
        {
            _processer.StopStatusLogging();
            _sessionContainer.ClearSession(event.data.fd);
            std::cout << event.data.fd << "client Out" << std::endl;
            return false;
        }
        // 연결 에러
        else if (received.first == nullptr && received.second < 0)
        {
            _sessionContainer.ClearSession(event.data.fd);
            std::cerr << "ClientSockProcesses epoll_ctl Error: " << errno << std::endl;
            ::shutdown(event.data.fd, SHUT_RDWR);
            return false;
        }
        _processer.Process(received.first, session);
    }
    return true;
}

Server::~Server()
{
}