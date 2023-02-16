//
// Created by admin on 2023/2/15.
//

#include "tcpserver.h"
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
class TcpServer::TcpServerPrivate
{
public:
    TcpServerPrivate (int port, const std::string &host)
        : socket(port, host) {}

    TcpServer::CallbackType callback;
    SocketType socket;
    TcpError error {};
    struct epoll_event event {};
    static const int MAX_SIZE = 1024;
    char message[MAX_SIZE] {};
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
void TcpServer::listenError (const TcpError::ErrorCallback &fn)
{
    d->error.setErrorCallback(fn);
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
bool TcpServer::createEpoll ()
{
    int epfd = epoll_create1(0);

    if (epfd == -1)
    {
        d->error.setError("epoll_create error");
        return false;
    }

    d->event.data.fd = fd();
    // 对应的文件描述符可读 | 将EPOLL设置成边缘触发
    // 区别是，LT 模式下只要一个句柄上的事件一次没有处理完，会在以后调用 epoll_wait 时次次返回这个句柄。而ET模式仅在第一次返回。
    d->event.events = EPOLLIN | EPOLLET;
    // 注册server epoll
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd(), &d->event);
    waitEpoll(epfd);
}
void TcpServer::waitEpoll (int epfd)
{
    // 一次最多处理20个连接
    const int MAX_SIZE = 20;
    struct epoll_event events[MAX_SIZE];
    int connectNum;

    while (true)
    {
        // 返回0表示超时或没有连接
        connectNum = epoll_wait(epfd, events, MAX_SIZE, 500);
        for (int i = 0; i < connectNum; ++i)
        {
            // 如果监听到一个新的socket用户绑定到了socket监听端口，建立连接
            if (events[i].data.fd == fd())
                createConnect(epfd);
                // 如果已创建连接，并且受到数据
            else if (events[i].events & EPOLLIN)
                inHandler(epfd, &events[i]);
        }
    }
}
void TcpServer::createConnect (int epfd)
{
    static struct sockaddr_in clientAddr {};
    int connectFd = accept(fd(), (sockaddr *)&clientAddr, nullptr);
    if (connectFd == -1)
        d->error.setError("accept error");

    char *ip = inet_ntoa(clientAddr.sin_addr);
    int port = ntohs(clientAddr.sin_port);

    d->event.data.fd = connectFd;
    d->event.events = EPOLLIN | EPOLLET;
    // 注册client epoll
    epoll_ctl(epfd, EPOLL_CTL_ADD, connectFd, &d->event);
}
void TcpServer::inHandler (int epfd, struct epoll_event *event)
{
    int socketFd = event->data.fd;
    if (socketFd == -1)
        return;

    ssize_t n;
    static std::string message;
    while ((n = recv(socketFd, d->message, TcpServerPrivate::MAX_SIZE, 0)) > 0)
    {
        if (n == TcpServerPrivate::MAX_SIZE)
            message += d->message;
        else
            for (int i = 0; i < n; ++i)
            {
                message += d->message[i];
            }
    }

    if (n == -1)
        d->error.setError("readLine error");
        // 0直接认为关闭了连接
    else if (n == 0)
    {
        // 长连接  先不做处理
        // ::close(socketFd);
        // event->data.fd = -1;
    }

    d->socket.setMessage(message);
    if (d->callback)
        d->callback(d->socket);

    event->events = EPOLLOUT | EPOLLET;
    //修改socketFd上要处理的事件为EPOLLOUT
    epoll_ctl(epfd, EPOLL_CTL_MOD, socketFd, event);
}