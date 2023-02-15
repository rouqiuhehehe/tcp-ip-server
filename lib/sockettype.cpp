//
// Created by admin on 2023/2/15.
//

#include "sockettype.h"

class SocketType::SocketTypePrivate
{
public:
    SocketTypePrivate (int p, const std::string h)
        : port(p), host(h) {}
    int port;
    std::string host;
};
SocketType::SocketType (int port, const std::string &host)
    : d(new SocketTypePrivate(port, host)) {}
SocketType::~SocketType ()
{
    delete d;
}
int SocketType::port () const
{
    return d->port;
}
std::string SocketType::host () const
{
    return d->host;
}