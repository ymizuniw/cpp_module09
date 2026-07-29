# include "CSVParser.hpp"
# include <map>

class InputFile: public CSVParser {
    private:
    public:
        InputFile();
        InputFile(const InputFile &other);
        InputFile &operator=(const InputFile &other);
        ~InputFile();
        void checkFile();
        void parseFile();
        void sortRecord(); 
        std::multimap<Date,float> getRecord();
};
