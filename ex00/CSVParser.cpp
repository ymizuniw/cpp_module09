# include "CSVParser.hpp"

CSVParser::CSVParser(): errs_(){}

CSVParser::CSVParser(std::string file_name):file_name_(file_name){}

CSVParser::CSVParser(std::string file_name, std::vector<Error> errs,std::string fmt): file_name_(file_name), errs_(errs), fmt_(fmt) {}

CSVParser::CSVParser(const CSVParser &other){
    if (this==&other)
        return ;
    record_=other.record_;
    file_name_=other.file_name_;
    std::cout << "CSVParser's copy constructor called. This is not for real use." << std::endl;
    // file_stream_=other.file_stream_;
    errs_=other.errs_;
    fmt_=other.fmt_;
}

CSVParser &CSVParser::operator=(const CSVParser &other){
    if (this==&other)
        return(*this);
    record_=other.record_;
    file_name_=other.file_name_;
    std::cout << "CSVParser's copy constructor called. This is not for real use." << std::endl;
    // file_stream_=other.file_stream_;
    errs_=other.errs_;
    fmt_=other.fmt_;
    return (*this);
}
