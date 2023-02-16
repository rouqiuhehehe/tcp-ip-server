//
// Created by admin on 2023/2/15.
//

#ifndef TCP_IP_SERVER_LIB_SOCKETTYPE_H_
#define TCP_IP_SERVER_LIB_SOCKETTYPE_H_

#include <string>
class SocketType
{
    friend class TcpServer;
public:
    SocketType (int port, const std::string &host);
    ~SocketType ();
    [[nodiscard]] inline int port () const;
    [[nodiscard]] inline std::string host () const;
    [[nodiscard]] inline std::string message () const;
    inline void write (const std::string &str);

private:
    inline void setMessage (const std::string &msg);
    inline void setEvent (int epfd, struct epoll_event *event);

private:
    class SocketTypePrivate;
    SocketTypePrivate *d;
};

#endif //TCP_IP_SERVER_LIB_SOCKETTYPE_H_
