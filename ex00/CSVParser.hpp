# ifndef CSV_PARSER_HPP
# define CSV_PARSER_HPP

# include <map>
# include "Date.hpp"

class CSVParser {
    private:
        std::multimap<Date,float> record_;
    public:
        CSVParser();
        CSVParser(const CSVParser &other);
        CSVParser &operator=(const CSVParser &other);
        ~CSVParser();
        virtual void checkFile() = 0;
        virtual void parseFile() = 0;
        virtual void sortRecord() = 0;
        virtual std::multimap<Date,float> getRecord() = 0;
};

# endif
