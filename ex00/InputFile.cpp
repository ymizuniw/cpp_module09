#include "InputFile.hpp"
#include "Error.hpp"
#include "ParseDate.hpp"
#include "ParseValue.hpp"
#include <iostream>

InputFile::InputFile() : CSVParser() {}

InputFile::InputFile(std::string file_name) : CSVParser(file_name, '|', "date | value") {}

InputFile::InputFile(const InputFile& other) : CSVParser(other) {}

InputFile& InputFile::operator=(const InputFile& other)
{
    if (this == &other)
        return (*this);
    CSVParser::operator=(other);
    return (*this);
}

InputFile::~InputFile() {}

void InputFile::openFile()
{
    file_stream_.open(file_name_.c_str(), std::ios_base::in);
    if (file_stream_.fail())
        throw std::runtime_error("Input: Could not open file: " + file_name_);
    file_stream_.exceptions(std::ios_base::badbit);
}

void InputFile::checkFormat()
{
    std::string line;

    if (std::getline(file_stream_, line)) {
        if (line != fmt_)
            throw std::runtime_error("Input: Invalid Format: " + line);
    }
}

void InputFile::parseFile()
{
    std::string line;
    int line_num = 2;

    while (std::getline(file_stream_, line)) {
        std::vector<std::string> tokens = splitLine(line);

        if (tokens.size() != 2 || tokens[0].empty() || tokens[1].empty()) {
            std::cout << "Error: bad input => " << line << std::endl;
            line_num++;
            continue;
        }
        size_t len = tokens[0].length();
        if (tokens[0][len - 1] != ' ' || tokens[1][0] != ' ') {
            std::cout << "Error: bad input => " << line << std::endl;
            line_num++;
            continue;
        }
        tokens[0].erase(len - 1, 1);
        tokens[1].erase(0, 1);

        Error err(0, line_num, "");
        Date date = parseDate(tokens[0], err);
        float value = parseValue(tokens[1], err);
        date.setError(err.err_num, err.line_num, err.err_msg);
        record_.insert(std::make_pair(date, value));
        line_num++;
    }
}

void InputFile::sortRecord() {}

std::multimap<Date, float> InputFile::getRecord()
{
    return (record_);
}
