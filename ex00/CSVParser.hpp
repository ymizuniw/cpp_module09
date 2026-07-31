#ifndef CSV_PARSER_HPP
#define CSV_PARSER_HPP

#include "Date.hpp"
#include <fstream>
#include <map>
#include <vector>

class CSVParser
{
  protected:
    std::ifstream file_stream_;
    std::multimap<Date, float> record_;
    std::string file_name_;
    std::string fmt_;
    char delim_;
    std::vector<std::string> splitLine(std::string& line) const;

  public:
    CSVParser();
    CSVParser(std::string file_name, char delim, std::string fmt);
    CSVParser(const CSVParser& other);
    CSVParser& operator=(const CSVParser& other);
    virtual ~CSVParser();
    virtual void openFile() = 0;
    virtual void checkFormat() = 0;
    virtual void parseFile() = 0;
    virtual void sortRecord() = 0;
    virtual std::multimap<Date, float> getRecord() = 0;
};

#endif
