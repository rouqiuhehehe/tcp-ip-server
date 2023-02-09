//
// Created by admin on 2023/2/9.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
int main (int argc, char *argv[])
{
    int server_socket;
    int client_socket;

    struct sockaddr_in server_address {};
    struct sockaddr_in client_address {};
    socklen_t client_address_len;
    const char *message = "hello world";

    std::cout << argc;
    std::cout << argv;

    return 0;
}