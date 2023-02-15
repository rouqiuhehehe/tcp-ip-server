//
// Created by admin on 2023/2/15.
//

#include "tcpserver.h"
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
class TcpServer::TcpServerPrivate
{
public:
    TcpServerPrivate (int port, const std::string &host)
        : socket(port, host) {}

    TcpServer::CallbackType callback;
    SocketType socket;
    TcpError error {};
};
TcpServer::TcpServer (const TcpServer::CallbackType &fn)
    : d(new TcpServerPrivate(port(), host()))
{
    d->callback = fn;
}
TcpServer::~TcpServer ()
{
    delete d;
}
bool TcpServer::listen (int port)
{
    setPort(port);
    setHost("127.0.0.1");

    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd == -1) [[unlikely]]
    {
        d->error.setError("create socket error");
        return false;
    }
    setFd(fd);

    if (bind(
        fd,
        (const struct sockaddr *)&getSockaddr(),
        sizeof(getSockaddr())) == -1) [[unlikely]]
    {
        d->error.setError("bind error");
        return false;
    }

    if (::listen(fd, SOMAXCONN) == -1)
    {
        d->error.setError("listen error");
        return false;
    }
}
TcpError TcpServer::lastError () const
{
    return d->error;
}
