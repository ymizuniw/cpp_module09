# include "DBFile.hpp"
# include "ParseDate.hpp"
# include "ParseValue.hpp"

DBFile::DBFile(): CSVParser() {};
DBFile::DBFile(std::string file_name): CSVParser(file_name,',',true){};
DBFile::DBFile(const DBFile &other){ if (this==&other) return ;}
DBFile &DBFile::operator=(const DBFile &other){if (this==&other) return(*this) ; record_=other.record_; file_name_=other.file_name_; return (*this);}
DBFile::~DBFile(){}

std::vector<std::string> split_line(std::string &line, char delim)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(line);

    iss.exceptions(std::ios_base::badbit);
    while (std::getline(iss, token, delim))
            tokens.push_back(token);
    return (tokens);
}

void sortRecord(){
    // map is sorted automatically
}

std::multimap<Date,float> getRecord(){}
