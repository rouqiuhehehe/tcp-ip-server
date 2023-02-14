//
// Created by admin on 2023/2/13.
//
#include <iostream>
#include "util.h"
#include <arpa/inet.h>
#include <bitset>
int main ()
{
    uint16_t hostPort = 0x1234;
    uint16_t netPort;
    uint32_t hostAddr = 0x12345678;
    uint32_t netAddr;

    netPort = htons(hostPort);
    netAddr = htonl(hostAddr);

    std::cout << std::hex
              << "hostPort：" << hostPort << std::endl
              << "netPort：" << netPort << std::endl
              << "hostAddr：" << hostAddr << std::endl
              << "netAddr：" << netAddr << std::endl;

    std::cout << std::bitset <32>(hostAddr) << std::endl;
    return 0;
}