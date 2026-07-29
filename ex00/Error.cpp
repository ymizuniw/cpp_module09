# include "Error.hpp"

Error::Error(): err_num(-1), line_num(-1), err_msg("")
{}

Error::Error(int err_num, int line_num, std::string err_msg): err_num(err_num), line_num(line_num), err_msg(err_msg)
{}

void set_error(Error &err, int err_num, int line_num, std::string err_msg)
{
    if (err.err_num!=0)
        return ;
    err.err_num = err_num;
    err.line_num = line_num;
    err.err_msg = err_msg;
}
