#include "Error.hpp"

Error::Error() : err_num(-1), line_num(-1), err_msg("") {}

Error::Error(int err_num, int line_num, std::string err_msg)
    : err_num(err_num), line_num(line_num), err_msg(err_msg)
{
}

void Error::setError(int err_num, int line_num, std::string err_msg)
{
    if (this->err_num != 0)
        return;
    this->err_num = err_num;
    this->line_num = line_num;
    this->err_msg = err_msg;
}
