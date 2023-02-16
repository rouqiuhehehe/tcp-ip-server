//
// Created by admin on 2023/2/15.
//

#ifndef TEST_LIB_TCPERROR_H_
#define TEST_LIB_TCPERROR_H_

#include <exception>
#include <string>
#include <cstring>
#include <functional>
class TcpError : public std::exception
{
public:
    typedef std::function <void (std::string)> ErrorCallback;

    inline void setError (std::string err);
    [[nodiscard]] inline const char *what () const noexcept override;
    inline void setErrorCallback (const ErrorCallback &fn);

private:
    std::string error;
    ErrorCallback errorCallback;
};
const char *TcpError::what () const noexcept
{
    return error.c_str();
}
void TcpError::setError (std::string err)
{
    error = std::move(err);
    error = error + "：" + std::strerror(errno);

    if (errorCallback)
        errorCallback(error);
}
void TcpError::setErrorCallback (const TcpError::ErrorCallback &fn)
{
    errorCallback = fn;
}

#endif //TEST_LIB_TCPERROR_H_
