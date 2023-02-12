//
// Created by Administrator on 2023/2/11.
//

#ifndef TEST__UTIL_H_
#define TEST__UTIL_H_
#include <string>
#include <iostream>
#include <fstream>

class Utils
{
private:
    class FileDescriptorHelper : public std::filebuf
    {
    public:
        int handle () { return _M_file.fd(); }
    };
public:
    // 获取文件描述符
    static int getFileDescriptor (std::ifstream &fs)
    {
        auto *buf = fs.rdbuf();

        return static_cast<FileDescriptorHelper *>(buf)->handle(); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    }
    static int getFileDescriptor (std::ofstream &fs)
    {
        auto *buf = fs.rdbuf();

        return static_cast<FileDescriptorHelper *>(buf)->handle(); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    }
    static int getFileDescriptor (std::fstream &fs)
    {
        auto *buf = fs.rdbuf();

        return static_cast<FileDescriptorHelper *>(buf)->handle(); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    }
    static inline void failExit (const std::string &str)
    {
        std::cerr << str << std::endl;
        exit(EXIT_FAILURE);
    }
};
#endif //TEST__UTIL_H_
