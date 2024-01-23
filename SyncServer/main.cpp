#include "Server/Server.hpp"

int main()
{
    Server server(3334, 1);
    if (server.initServer() < 0)
    {
        return 0;
    }
    if (server.RunServer())
    {
        return 0;
    }
}