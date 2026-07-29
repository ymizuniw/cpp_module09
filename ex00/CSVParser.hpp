# ifndef CSV_PARSER_HPP
# define CSV_PARSER_HPP

# include <map>
# include "Date.hpp"
# include <fstream>
# include <iostream>
# include <sstream>
# include "ParseDate.hpp"
# include "ParseValue.hpp"

class CSVParser {
    private:
        std::ifstream file_stream_;
        bool exception_;
    protected:
        std::multimap<Date,float> record_;
        std::string file_name_;
        std::string fmt_;
        char delim_;
    public:
        CSVParser();
        CSVParser(std::string file_name, char delim, bool exception);
        CSVParser(std::string file_name, std::vector<Error> errs,std::string fmt, char delim, bool exception);
        CSVParser(const CSVParser &other);
        CSVParser &operator=(const CSVParser &other);
        virtual ~CSVParser();
        void openFile();
        void checkFormat();
        void parseFile();
        void sortRecord();
        void setException(bool exception);
        virtual std::multimap<Date,float> getRecord() = 0;
};

# endif
