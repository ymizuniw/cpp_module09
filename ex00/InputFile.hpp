# include "CSVParser.hpp"
# include <map>
# include <fstream>

class InputFile: public CSVParser {
    private:
        std::multimap<Date,float> record_;
        std::string file_name_;
        std::ifstream file_stream_;
        std::vector<Error> errs_;
        std::string fmt_;
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
