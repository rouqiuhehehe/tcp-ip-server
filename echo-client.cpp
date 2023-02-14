//
// Created by admin on 2023/2/14.
//
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include "util.h"

int main (int argc, char **argv)
{
    const int BUFFER_SIZE = 1024;
    char message[BUFFER_SIZE];
    int serverSocket;
    struct sockaddr_in serverAddr {};
    int messageSize;

    if (argc != 3)
        Utils::failExit(std::string("Usage : ") + argv[0] + "<IP> <port>");

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
        Utils::failExit("socket error");

    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(
        serverSocket,
        (struct sockaddr *)&serverAddr,
        sizeof(serverAddr)) == -1)
        Utils::failExit("connect error");
    else
        std::cout << "connected......." << std::endl;

    std::string str;
    while (true)
    {
        std::cout << "输入字符串（Q退出）：" << std::endl;
        std::getline(std::cin, str);
        if (str == "q" | str == "Q")
            break;

        write(serverSocket, str.c_str(), str.size());
        messageSize = (int)read(serverSocket, message, BUFFER_SIZE - 1);
        message[messageSize] = '\0';
        std::cout << "message from server：" << message << std::endl;
    }

    close(serverSocket);
    return 0;
}