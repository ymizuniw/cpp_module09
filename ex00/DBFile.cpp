# include "DBFile.hpp"
# include "ParseDate.hpp"
# include "ParseValue.hpp"
# include "Error.hpp"

DBFile::DBFile(): CSVParser() {}
DBFile::DBFile(std::string file_name): CSVParser(file_name, ',', "date,exchange_rate") {}
DBFile::DBFile(const DBFile &other): CSVParser(other) {}
DBFile &DBFile::operator=(const DBFile &other){
    if (this==&other)
        return (*this);
    CSVParser::operator=(other);
    return (*this);
}
DBFile::~DBFile(){}

void DBFile::openFile(){
    file_stream_.open(file_name_.c_str(), std::ios_base::in);
    file_stream_.exceptions(std::ios_base::badbit);
}

void DBFile::checkFormat(){
    std::string line;

    if (std::getline(file_stream_, line))
    {
        if (line!=fmt_)
            throw std::runtime_error("DB: Invalid Format: " + line);
    }
}

void DBFile::parseFile(){
    std::string line;
    int line_num = 1;

    while (std::getline(file_stream_, line))
    {
        std::vector<std::string> tokens = splitLine(line);
        if (tokens.size()!=2)
            throw std::runtime_error("DB: Invalid line format: " + std::to_string(line_num));

        Error err(0, line_num, "");
        Date date = parseDate(tokens[0], err);
        float value = parseValue(tokens[1], err);
        if (err.err_num!=0)
            throw std::runtime_error("DB: " + err.err_msg);
        record_.insert(std::make_pair(date, value));
        line_num++;
    }
}

void DBFile::sortRecord(){
}

std::multimap<Date,float> DBFile::getRecord(){
    return (record_);
}
