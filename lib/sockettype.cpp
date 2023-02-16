//
// Created by admin on 2023/2/15.
//

#include "sockettype.h"
#include <utility>
#include <sys/epoll.h>

class SocketType::SocketTypePrivate
{
public:
    SocketTypePrivate (int p, std::string h)
        : port(p), host(std::move(h)) {}
    int port;
    std::string host;
    std::string message;
    std::string writeMessage;
    struct epoll_event *event = nullptr;
    int epfd = -1;
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
void SocketType::write (const std::string &str)
{
    d->writeMessage = str;

    // 调用write函数时修改
    d->event->events = EPOLLOUT | EPOLLET;
    //修改socketFd上要处理的事件为EPOLLOUT
    epoll_ctl(d->epfd, EPOLL_CTL_MOD, d->event->data.fd, d->event);
}
void SocketType::setEvent (int epfd, struct epoll_event *event)
{
    d->epfd = epfd;
    d->event = event;
}