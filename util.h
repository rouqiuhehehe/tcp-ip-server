//
// Created by Administrator on 2023/2/11.
//

#ifndef TEST__UTIL_H_
#define TEST__UTIL_H_
#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <utility>
class UtilsError final : public std::exception
{
public:
    UtilsError () = default;
    explicit UtilsError (std::string str)
        : error(std::move(str)) {}
    void setError (std::string str) { error = std::move(str); }
    [[nodiscard]] const char *what () const noexcept final
    {
        return error.c_str();
    }
private:
    std::string error = "success";
};
class Utils
{
private:
    class FileDescriptorHelper : public std::filebuf
    {
    public:
        int handle () { return _M_file.fd(); }
    };
public:
    enum class Endian
    {
        BIG_ENDIAN_,
        LITTLE_ENDIAN_
    };
    // 获取文件描述符
    static inline int getFileDescriptor (std::ifstream &fs);

    static inline int getFileDescriptor (std::ofstream &fs);
    static inline int getFileDescriptor (std::fstream &fs);
    static inline void failExit (const std::string &str);
    static bool copyFile (const std::string &filePath,
        const std::string &copyPath);
    static UtilsError lastError () { return error; }
    static inline Endian getEndian ();

private:
    static UtilsError error;
};
UtilsError Utils::error = UtilsError();
bool Utils::copyFile (const std::string &filePath, const std::string &copyPath)
{
    std::ifstream file(filePath);

    if (!file)
    {
        error.setError("open file fail in " + filePath);
        return false;
    }

    std::ofstream copyFile(copyPath, std::ios_base::out | std::ios_base::trunc);
    std::string context;
    while (!file.eof())
    {
        getline(file, context);
        copyFile << context;
    }

    file.close();
    copyFile.close();

    return true;
}
Utils::Endian Utils::getEndian ()
{
    int i = 1;
    char s = *(char *)&i;
    if (s == 1)
        return Utils::Endian::LITTLE_ENDIAN_;

    return Utils::Endian::BIG_ENDIAN_;
}
int Utils::getFileDescriptor (std::ifstream &fs)
{
    auto *buf = fs.rdbuf();

    return static_cast<FileDescriptorHelper *>(buf)->handle(); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
}
int Utils::getFileDescriptor (std::ofstream &fs)
{
    auto *buf = fs.rdbuf();

    return static_cast<FileDescriptorHelper *>(buf)->handle(); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
}
int Utils::getFileDescriptor (std::fstream &fs)
{
    auto *buf = fs.rdbuf();

    return static_cast<FileDescriptorHelper *>(buf)->handle(); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
}
void Utils::failExit (const std::string &str)
{
    std::cerr << str << std::endl;
    exit(EXIT_FAILURE);
}
#endif //TEST__UTIL_H_
