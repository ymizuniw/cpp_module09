# include "Date.hpp"
# include "CSVParser.hpp"
# include <fstream>
# include <sstream>
# include "Error.hpp"

class DBFile : public CSVParser {
    public:
        DBFile();
        DBFile(std::string file_name);
        DBFile(const DBFile &other);
        DBFile &operator=(const DBFile &other);
        ~DBFile();
        void openFile();
        void checkFile();
        void parseFile();
        void sortRecord();
        std::multimap<Date,float> getRecord();
};
