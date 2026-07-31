#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>

struct Error {
    int err_num;
    int line_num;
    std::string err_msg;
    Error();
    Error(int err_num, int line_num, std::string err_msg);
    void setError(int err_num, int line_num, std::string err_msg);
};

#endif
