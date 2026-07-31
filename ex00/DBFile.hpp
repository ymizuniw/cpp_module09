#include "CSVParser.hpp"
#include "Date.hpp"

class DBFile : public CSVParser
{
  public:
    DBFile();
    DBFile(std::string file_name);
    DBFile(const DBFile& other);
    DBFile& operator=(const DBFile& other);
    ~DBFile();
    void openFile();
    void checkFormat();
    void parseFile();
    void sortRecord();
    std::multimap<Date, float> getRecord();
};
