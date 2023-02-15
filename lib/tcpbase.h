//
// Created by Administrator on 2023/2/14.
//

#ifndef TEST_LIB_TCPBASE_H_
#define TEST_LIB_TCPBASE_H_
#include <string>
#include <arpa/inet.h>
#include "nocopybase.h"
class TcpBase : public NoCopyBase
{
protected:
    TcpBase ();
    virtual ~TcpBase ();

public:
    inline void setHost (const std::string &host);
    inline void setPort (int port);
    inline void setFd (int fd);
    [[nodiscard]] inline int port () const;
    [[nodiscard]] inline std::string host () const;
    [[nodiscard]] inline int fd () const;
    inline void close () const;

protected:
    [[nodiscard]] inline struct sockaddr_in& getSockaddr() const;
private:
    class TcpBasePrivate;
    TcpBasePrivate *d;
};

#endif //TEST_LIB_TCPBASE_H_
