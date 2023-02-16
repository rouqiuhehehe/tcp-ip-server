//
// Created by admin on 2023/2/15.
//

#include "sockettype.h"

#include <utility>

class SocketType::SocketTypePrivate
{
public:
    SocketTypePrivate (int p, std::string h)
        : port(p), host(std::move(h)) {}
    int port;
    std::string host;
    std::string message;
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
std::string SocketType::message () const
{
    return d->message;
}
void SocketType::setMessage (const std::string &msg)
{
    d->message = msg;
}
