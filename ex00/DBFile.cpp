# include "DBFile.hpp"
# include "ParseDate.hpp"
# include "ParseValue.hpp"

DBFile::DBFile(): CSVParser() {};
DBFile::DBFile(std::string file_name): CSVParser(file_name){};
DBFile::DBFile(const DBFile &other){ if (this==&other) return ;}
DBFile &DBFile::operator=(const DBFile &other){if (this==&other) return(*this) ; record_=other.record_; file_name_=other.file_name_; return (*this);}
DBFile::~DBFile(){}

void DBFile::openFile(){
    file_stream_.open(file_name_, std::ios_base::in);
    file_stream_.exceptions(std::ios_base::badbit);
}

void DBFile::checkFile(){
    std::string format = "date,exchange_rate";
    std::string line;

    if (std::getline(file_stream_, line))
    {
        if (line!=format)
            throw std::runtime_error("DB: Invalid Format" + line);
    }
}

std::vector<std::string> split_line(std::string &line, const char delim)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(line);

    iss.exceptions(std::ios_base::badbit);
    while (std::getline(iss, token, delim))
            tokens.push_back(token);
    return (tokens);
}

void DBFile::parseFile(){
    const char delim = ',';

    std::vector<std::vector<std::string> > nodes;
    std::string line;
    int line_num = 1;

    while (std::getline(file_stream_, line))
    {
        std::vector<std::string> tokens = split_line(line, delim);
        if (tokens.size()!=2)
            throw std::runtime_error("DB: Invalid line format: " + std::to_string(line_num));
        nodes.push_back(tokens);
        line_num++;
    }

    std::vector<std::vector<std::string> >::const_iterator it = nodes.cbegin();
    std::vector<std::vector<std::string> >::const_iterator end_it = nodes.cend();

    line_num = 1;
    while (it!=end_it)
    {
        Error err(0,line_num,"");
        Date date = parseDate((*it)[0],err);
        float value = parseValue((*it)[1],err);
        record_.insert(std::make_pair(date, value));
    }
}

void sortRecord(){
    // map is sorted automatically
}
std::multimap<Date,float> getRecord(){}
