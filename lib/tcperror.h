//
// Created by admin on 2023/2/15.
//

#ifndef TEST_LIB_TCPERROR_H_
#define TEST_LIB_TCPERROR_H_

#include <exception>
#include <string>
#include <cstring>
class TcpError : public std::exception
{
public:
    inline void setError (std::string err);
    [[nodiscard]] inline const char *what () const noexcept override;

private:
    std::string error;
};
const char *TcpError::what () const noexcept
{
    return error.c_str();
}
void TcpError::setError (std::string err)
{
    error = std::move(err);
    error = error + "：" + std::strerror(errno);
}

#endif //TEST_LIB_TCPERROR_H_
