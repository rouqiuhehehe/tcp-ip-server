//
// Created by admin on 2023/2/9.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <csignal>

void failExit (const std::string &str)
{
    std::cerr << str << std::endl;
    exit(EXIT_FAILURE);
}
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
int main (int argc, char *argv[])
{
    int server_socket;
    int client_socket;

    struct sockaddr_in server_address {};
    struct sockaddr_in client_address {};
    socklen_t client_address_len;
    const char message[] = "hello world";
    int port = getArgPort(argc, argv);

    // domain 地址族 PF_INET ip4, PF_INET6 ip6
    // type 数据传输方式/套接字类型 SOCK_STREAM（流格式套接字/面向连接的套接字） 和 SOCK_DGRAM（数据报套接字/无连接的套接字）
    // protocol 表示传输协议，常用的有 IPPROTO_TCP 和 IPPTOTO_UDP，分别表示 TCP 传输协议和 UDP 传输协议 (只有一种协议满足条件，可以将 protocol 的值设为 0)
    server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
        failExit("create socket error");

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);

    if (bind(
        server_socket,
        (struct sockaddr *)&server_address,
        sizeof(server_address)) == -1)
        failExit("bind error");

    if (listen(server_socket, 5) == -1)
        failExit("listen error");

    client_address_len = sizeof(client_address);
    // 阻塞代码执行，直到有新的请求进来
    client_socket = accept(
        server_socket,
        (struct sockaddr *)&client_address,
        &client_address_len
    );
    if (client_socket == -1)
        failExit("accept error");

    write(client_socket, message, sizeof(message));
    close(client_socket);
    close(server_socket);

    return 0;
}