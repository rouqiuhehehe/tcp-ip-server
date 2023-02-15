//
// Created by Administrator on 2023/2/14.
//

#include "tcpbase.h"
#include <sys/socket.h>

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
    int fd {};
};
TcpBase::TcpBase ()
    : d(new TcpBasePrivate)
{
}
TcpBase::~TcpBase ()
{
    delete d;
}
void TcpBase::setHost (const std::string &host)
{
    d->setHost(host);
}
void TcpBase::setPort (int port)
{
    d->setPort(port);
}
void TcpBase::close () const
{
    ::close(d->fd);
}
std::string TcpBase::host () const
{
    return inet_ntoa(d->serverSocket.sin_addr);
}
int TcpBase::port () const
{
    return ntohs(d->serverSocket.sin_port);
}
void TcpBase::setFd (int fd)
{
    d->fd = fd;
}
int TcpBase::fd () const
{
    return d->fd;
}
struct sockaddr_in &TcpBase::getSockaddr () const
{
    return d->serverSocket;
}

