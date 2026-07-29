# ifndef CSV_PARSER_HPP
# define CSV_PARSER_HPP

# include <map>
# include "Date.hpp"
# include <fstream>
# include <iostream>

class CSVParser {
    private:
        std::multimap<Date,float> record_;
        std::string file_name_;
        std::ifstream file_stream_;
        std::vector<Error> errs_;
        std::string fmt_;
    public:
        CSVParser();
        CSVParser(std::string file_name);
        CSVParser(std::string file_name, std::vector<Error> errs,std::string fmt);
        CSVParser(const CSVParser &other);
        CSVParser &operator=(const CSVParser &other);
        virtual ~CSVParser();
        virtual void openFile() = 0;
        virtual void checkFile() = 0;
        virtual void parseFile() = 0;
        virtual void sortRecord() = 0;
        virtual std::multimap<Date,float> getRecord() = 0;
};

# endif
