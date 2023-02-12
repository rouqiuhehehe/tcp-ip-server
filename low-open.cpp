//
// Created by Administrator on 2023/2/11.
//
#include "util.h"
#include <fstream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

void createFile ();
void readFile ();
int main ()
{
    createFile();
    readFile();

    return 0;
}

void createFile ()
{
    char buffer[] = "Let's go!\n";

    std::ofstream fd;
    fd.open("data.txt", std::ios_base::trunc | std::ios_base::out);
    if (!fd.is_open())
        Utils::failExit(std::strerror(errno));

    fd << buffer;
    fd.close();
}

void readFile ()
{
    std::ifstream fd;
    fd.open("data.txt", std::ios_base::in);

    if (!fd.is_open())
        Utils::failExit(std::strerror(errno));

    std::cout << "文件描述符：" << Utils::getFileDescriptor(fd) << std::endl;
    std::string str;
    std::cout << "下面是读取到的文件内容：" << std::endl;
    while (!fd.eof())
    {
        getline(fd, str);
        std::cout << str;
        str.clear();
    }
}