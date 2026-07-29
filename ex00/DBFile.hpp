# include "Date.hpp"
# include "CSVParser.hpp"

class DBFile : public CSVParser {
    private:
    public:
        DBFile();
        DBFile(const DBFile &other);
        DBFile &operator=(const DBFile &other);
        ~DBFile();
        void checkFile();
        void parseFile();
        void sortRecord();
        std::multimap<Date,float> getRecord();
};
