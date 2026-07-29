# include "CSVParser.hpp"

CSVParser::CSVParser() {}

CSVParser::CSVParser(std::string file_name, char delim, bool exception):file_name_(file_name), delim_(delim), exception_(exception) {}

CSVParser::CSVParser(std::string file_name, std::vector<Error> errs,std::string fmt, char delim, bool exception): file_name_(file_name), errs_(errs), fmt_(fmt), delim_(delim), exception_(exception) {}

CSVParser::CSVParser(const CSVParser &other): exception_(other.exception_){
    if (this==&other)
        return ;
    record_=other.record_;
    file_name_=other.file_name_;
    std::cout << "CSVParser's copy constructor called. This is not for real use." << std::endl;
    // file_stream_=other.file_stream_;
    fmt_=other.fmt_;
    delim_=other.delim_;
}

CSVParser &CSVParser::operator=(const CSVParser &other){
    if (this==&other)
        return(*this);
    record_=other.record_;
    file_name_=other.file_name_;
    std::cout << "CSVParser's copy constructor called. This is not for real use." << std::endl;
    // file_stream_=other.file_stream_;
    fmt_=other.fmt_;
    return (*this);
}

void CSVParser::openFile(){
    file_stream_.open(file_name_, std::ios_base::in);
    file_stream_.exceptions(std::ios_base::badbit);
}

void CSVParser::checkFormat(){
    std::string line;

    if (std::getline(file_stream_, line))
    {
        if (line!=fmt_)
            throw std::runtime_error("DB: Invalid Format" + line);
    }
}

static std::vector<std::string> split_line(std::string &line, char delim)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(line);

    iss.exceptions(std::ios_base::badbit);
    while (std::getline(iss, token, delim))
        tokens.push_back(token);
    return (tokens);
}

void CSVParser::setException(bool exception)
{
    exception_=exception;
}

void trim_spaces_from_input(std::vector<std::vector<std::string> > &nodes)
{
    std::vector<std::vector<std::string> >::iterator row_it = nodes.begin();
    std::vector<std::vector<std::string> >::iterator row_end = nodes.end();

    size_t line_num = 2;
    while (row_it!=row_end)
    {
        if ((*row_it)[0].empty() || (*row_it)[1].empty())
            throw std::runtime_error("Invalid line format");
        size_t len = (*row_it)[0].length();
        // date' '|' 'value
        if ((*row_it)[0][len-1]!=' ' || (*row_it)[1][0]!=' ')
          throw std::runtime_error("Invalid line format: " + std::to_string(line_num));
        (*row_it)[0].erase(len-1, 1);
        (*row_it)[1].erase(0,1);
        ++line_num;
        ++row_it;
    }
}

void CSVParser::parseFile(){
    std::vector<std::vector<std::string> > nodes;
    std::string line;
    int line_num = 1;

    while (std::getline(file_stream_, line))
    {
        std::vector<std::string> tokens = split_line(line, delim_);
        if (tokens.size()!=2)
            throw std::runtime_error("DB: Invalid line format: " + std::to_string(line_num));
        if (fmt_==" | ")
            trim_spaces_from_input(nodes);
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
