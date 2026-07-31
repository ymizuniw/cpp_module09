#include "CSVParser.hpp"
#include <iostream>
#include <sstream>

CSVParser::CSVParser() {}

CSVParser::CSVParser(std::string file_name, char delim, std::string fmt)
    : file_name_(file_name), fmt_(fmt), delim_(delim)
{
}

CSVParser::CSVParser(const CSVParser& other)
{
    if (this == &other)
        return;
    record_ = other.record_;
    file_name_ = other.file_name_;
    // std::cout << "CSVParser's copy constructor called. This is not for real use." << std::endl;
    // file_stream_=other.file_stream_;
    fmt_ = other.fmt_;
    delim_ = other.delim_;
}

CSVParser& CSVParser::operator=(const CSVParser& other)
{
    if (this == &other)
        return (*this);
    record_ = other.record_;
    file_name_ = other.file_name_;
    // std::cout << "CSVParser's copy constructor called. This is not for real use." << std::endl;
    // file_stream_=other.file_stream_;
    fmt_ = other.fmt_;
    delim_ = other.delim_;
    return (*this);
}

CSVParser::~CSVParser() {}

std::vector<std::string> CSVParser::splitLine(std::string& line) const
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(line);

    iss.exceptions(std::ios_base::badbit);
    while (std::getline(iss, token, delim_))
        tokens.push_back(token);
    return (tokens);
}
