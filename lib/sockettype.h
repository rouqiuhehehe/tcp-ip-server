//
// Created by admin on 2023/2/15.
//

#ifndef TCP_IP_SERVER_LIB_SOCKETTYPE_H_
#define TCP_IP_SERVER_LIB_SOCKETTYPE_H_

#include <string>
class SocketType
{
public:
    SocketType(int port, const std::string &host);
    ~SocketType ();
    [[nodiscard]] inline int port () const;
    [[nodiscard]] inline std::string host () const;

private:
    class SocketTypePrivate;
    SocketTypePrivate *d;
};

#endif //TCP_IP_SERVER_LIB_SOCKETTYPE_H_
