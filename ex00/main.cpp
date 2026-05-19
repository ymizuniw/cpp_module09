#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

typedef struct s_err_stat {
    int no_separator;
    int wrong_date;
    int wrong_value;

    int date_cannot_parse;
    int value_cannot_parse;
} t_err_stat;

int main(int argc, char **argv)
{
    if (argc!=2)
        return (1);
    std::ifstream input(argv[1]);
    if (input.fail())
        std::cout << "file could not be opned" << std::endl;
    std::string line;
    std::getline(input, line);
    std::getline(input, line);
    std::cout << line << std::endl;
    //4digits,-,2digits,-,2digits,space,|,space,1

    /*
        all the format errors
        1.no separator '|'
        2.wrong date -> further branches
        3.wrong value -> further branches
    */
    t_err_stat estat={0};
    std::string::iterator date_start = line.begin();
    std::string::iterator separator = std::find(line.begin(), line.end(),'|');
    
    if (separator==line.begin())
    {
        estat.date_cannot_parse = 1;
    }
    if (separator==line.end())
    {
        estat.no_separator = 1;
        estat.value_cannot_parse = 1;
    }
    else if (separator+1==line.end())
    {
        estat.value_cannot_parse = 1;
    }

    if (estat.no_separator)
    {
        std::cout << "Error: no_separator" << std::endl;
        return (1);
    }
    else if (estat.date_cannot_parse)
    {
        std::cout << "Error: date does not exist" << std::endl;
        return (1);
    }
    else if (estat.value_cannot_parse)
    {
        std::cout << "Error: value does not exist" << std::endl;
        return (1);
    }

    std::string::iterator date_end = separator - 1;
    std::string::iterator value_start = separator + 1;
    std::string::iterator value_end = line.end() - 1;

    std::cout << std::string(date_start, date_end) << std::endl;
    std::cout << std::string(separator, separator+1) << std::endl;
    std::cout << std::string(value_start, value_end+1) << std::endl;


    /*
        There are two options:
        1. firstly, separate by "|" for each date and value
        2. firstly, read and analyze input line from head to end.

    */

    /*
        In case separate by "|", start/end iterators of each date and value should be kept.
    */

    return (0);
}