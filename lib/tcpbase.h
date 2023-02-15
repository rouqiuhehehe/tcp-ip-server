//
// Created by Administrator on 2023/2/14.
//

#ifndef TEST_LIB_TCPBASE_H_
#define TEST_LIB_TCPBASE_H_
#include <string>
#include "nocopybase.h"
class TcpBase : public NoCopyBase
{
protected:
    TcpBase () = default;
    ~TcpBase ();

public:
    inline void host (const std::string &host);
    inline void port (int port);
    inline void close () const;
private:
    class TcpBasePrivate;
    TcpBasePrivate *d;
};

#endif //TEST_LIB_TCPBASE_H_
