//
// Created by admin on 2023/2/13.
//

#include <arpa/inet.h>
#include "util.h"
int main ()
{
    char *ip1 = "127.0.0.1";
    // char *ip2 = "127.0.0.256";
    char *addr = "127.232.124.79";

    in_addr_t convIP1 = inet_addr(ip1);
    if (convIP1 == INADDR_NONE)
        Utils::failExit(std::string("转换发生错误：") + ip1);
    else
        std::cout << "转换成功：" << ip1 << " to " << convIP1 << std::endl;

    // in_addr_t convIP2 = inet_addr(ip2);
    // if (convIP2 == INADDR_NONE)
    //     Utils::failExit(std::string("转换发生错误：") + ip2);
    // else
    //     std::cout << "转换成功：" << ip2 << " to " << convIP2 << std::endl;

    struct sockaddr_in addr_inet {};
    // 将ip地址转换成网络字节序，存入sockaddr_in.sin_addr
    if (!inet_aton(addr, &addr_inet.sin_addr))
        [[unlikely]]
            Utils::failExit(std::string("转换发生错误：") + addr);

    std::cout << "转换后的sockaddr_in地址：" << addr_inet.sin_addr.s_addr << std::endl;

    struct sockaddr_in addr_inet2 {};
    addr_inet2.sin_addr.s_addr = inet_addr("123.234.2.1");
    // 将网络字节序转换成ip地址
    std::string str = inet_ntoa(addr_inet.sin_addr);
    std::string str2 = inet_ntoa(addr_inet2.sin_addr);
    std::cout << str << std::endl << str2 << std::endl;

    std::cout << __builtin_return_address(0) << std::endl;

    return 0;
}