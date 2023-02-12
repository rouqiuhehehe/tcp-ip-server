//
// Created by admin on 2023/2/10.
//
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <csignal>

void failExit (const std::string &str)
{
    std::cerr << str;
    exit(EXIT_FAILURE);
}

int main (int argc, char **argv)
{
    int server_socket;
    struct sockaddr_in server_address {};
    char message[30];
    int str_len;
    int message_len = 0;

    if (argc != 3)
        failExit(std::string("Usage : ") + argv[0] + "<IP> <port>");

    server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
        failExit("socket error");

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    server_address.sin_port = htons(atoi(argv[2]));

    if (connect(
        server_socket,
        (struct sockaddr *)&server_address,
        sizeof(server_address)) == -1)
        failExit("connect fail");

    // while ((str_len = (int)read(server_socket, &message[message_len++], 1)))
    sleep(1);

    str_len = (int)read(server_socket, message, sizeof(message));
    if (str_len == -1)
        failExit("read error");

    std::cout << "接收到服务端的信息：" << message;
    close(server_socket);

    return 0;
}