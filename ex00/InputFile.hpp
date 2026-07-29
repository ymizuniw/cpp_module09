# include "CSVParser.hpp"
# include <map>
# include <fstream>

class InputFile: public CSVParser {
    public:
        InputFile();
        InputFile(std::string file_name);
        InputFile(const InputFile &other);
        InputFile &operator=(const InputFile &other);
        ~InputFile();
        void openFile();
        void checkFile();
        void parseFile();
        void sortRecord(); 
        std::multimap<Date,float> getRecord();
};
