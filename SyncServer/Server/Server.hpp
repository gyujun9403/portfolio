#include <iostream>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <memory>
#include <vector>
//#include "../MultiplexingModel/IMultiplexingModel.hpp"
//#include "../Session/SessionContainer.hpp"

#define THREAD_NUM 4

class Server
{
public:
    Server(int port, int maxClinetNum);
    bool initServer();
    bool RunServer();

private:
    //IMultiplexingModel _ioModel;
    //SessionContainer _sessionContainer;

    const int _PORT_NUM;
    const int _MAX_CLIENT_NUM;
    int _serverSockFd;
    sockaddr_in _serverAddr;

    std::unique_ptr<struct epoll_event[]> _epollEvents;
};