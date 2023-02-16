//
// Created by admin on 2023/2/15.
//

#ifndef TCP_IP_SERVER_LIB_TCPSERVER_H_
#define TCP_IP_SERVER_LIB_TCPSERVER_H_

#include "tcpbase.h"
#include <functional>
#include "sockettype.h"
#include "tcperror.h"
#include <sys/epoll.h>
class TcpServer : public TcpBase
{
public:
    typedef std::function <void (SocketType)> CallbackType;

    explicit TcpServer (const CallbackType &fn);
    ~TcpServer () override;

    void listenError (const TcpError::ErrorCallback &fn);
    bool listen (int port);
    [[nodiscard]] inline TcpError lastError () const;

private:
    bool createEpoll ();
    void waitEpoll (int epfd);
    void createConnect (int epfd);
    // 处理数据读取
    void inHandler (int epfd, struct epoll_event *events);
private:
    class TcpServerPrivate;
    TcpServerPrivate *d;
};

#endif //TCP_IP_SERVER_LIB_TCPSERVER_H_
