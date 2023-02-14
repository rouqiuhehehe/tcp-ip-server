//
// Created by admin on 2023/2/14.
//
#include "util.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>

int getArgPort (int argc, char *argv[])
{
    int port = 3000;
    if (argc >= 2)
    {
        char *endptr;
        port = (int)strtol(argv[1], &endptr, 10);
        if (endptr == argv[1])
        {
            std::cerr << "no header number in " << argv[1];
            exit(EXIT_FAILURE);
        }
        else if (errno == ERANGE)
        {
            std::cerr << "range error in " << argv[1];
            exit(EXIT_FAILURE);
        }
    }
    return port;
}
int main (int argc, char **argv)
{
    int serverSocket;
    int clientSocket;
    struct sockaddr_in serverAddr {};
    struct sockaddr_in clientAddr {};
    int port = getArgPort(argc, argv);
    const int CLIENT_MAX = 5;
    const int BUFFER_SIZE = 1024;
    socklen_t clientAddrSize = sizeof(clientAddr);

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    std::cout << serverSocket << std::endl;
    if (serverSocket == -1)
        [[unlikely]]
            Utils::failExit("create socket error");

    serverAddr.sin_port = htons(port);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(
        serverSocket,
        (const struct sockaddr *)&serverAddr,
        sizeof(serverAddr)) == -1)
        Utils::failExit("bind error");

    if (listen(serverSocket, CLIENT_MAX) == -1)
        Utils::failExit("listen error");

    for (int i = 0; i < CLIENT_MAX; ++i)
    {
        clientSocket = accept(
            serverSocket,
            (struct sockaddr *)&clientAddr,
            &clientAddrSize
        );

        if (clientSocket == -1)
            [[unlikely]]
                Utils::failExit("accept error");
        else
            std::cout << "连接成功：客户端" << i << std::endl;

        std::thread p(
            [=] ()
            {
                char message[BUFFER_SIZE];
                int messageSize;
                while ((messageSize =
                            (int)read(clientSocket, message, BUFFER_SIZE))
                    != 0)
                {
                    message[messageSize] = '\0';
                    std::cout << messageSize << std::endl;
                    std::string str = "收到客户端";
                    str += std::to_string(i + 1);
                    str += "发送的消息：";
                    str += message;
                    std::cout << str << std::endl;
                    write(clientSocket, str.c_str(), str.size());
                }
            }
        );

        p.detach();
    }
}