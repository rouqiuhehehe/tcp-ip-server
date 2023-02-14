//
// Created by Administrator on 2023/2/14.
//

#include "tcpbase.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class TcpBase::TcpBasePrivate
{
public:
    TcpBasePrivate ()
    {
        serverSocket.sin_family = AF_INET;
    }
    void setPort (int port)
    {
        serverSocket.sin_port = htons(port);
    }
    void setHost (const std::string &host)
    {
        inet_aton(host.c_str(), &serverSocket.sin_addr);
    }
    sockaddr_in serverSocket {};
    int socket {};
};
TcpBase::~TcpBase ()
{
    delete d;
}
void TcpBase::host (const std::string &host)
{
    d->setHost(host);
}
void TcpBase::port (int port)
{
    d->setPort(port);
}
void TcpBase::close () const
{
    ::close(d->socket);
}
