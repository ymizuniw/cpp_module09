# include "DBFile.hpp"
# include "InputFile.hpp"

class BitCoinRecord {
    private:
        std::multimap<Date,float> reference_record;
        DBFile db_;
        InputFile input_;
    public:
        void genRecord();
        void printReferenceRecord();
};
