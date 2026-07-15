#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

void check_csv_file(std::ifstream &file_stream, std::string format, bool db)
{
    // check the first line of csv
    std::string line;
    if (std::getline(file_stream, line))
    {
        if (line!=format)
        {
            if (db)
                throw std::runtime_error("DB: Invalid Format: " + line);
            throw std::runtime_error("Invalid Format" + line);
        }
    }
}

void check_fstream_open(std::ifstream &file_stream)
{
    if (!file_stream.is_open()){
        throw std::runtime_error("file could not be opened");
    }
}

// https://dexall.co.jp/articles/?p=2187#i-4
// in case of ",", it works. 
// in case of " | ", split by '|' and trimming spaces in the first and second substring.
std::vector<std::string> split_line(std::string &line, const char delim)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(line);

    iss.exceptions(std::ios_base::badbit);
    while (std::getline(iss, token, delim))
    {
        if (!token.empty()){
            tokens.push_back(token);
        }
    }
    return (tokens);
}

void print_tokens(std::vector<std::vector<std::string>> &nodes)
{
    std::vector<std::vector<std::string>>::iterator row_it = nodes.begin();
    std::vector<std::vector<std::string>>::iterator row_end = nodes.end();

    while (row_it!=row_end)
    {
        std::cout << (*row_it)[0] << std::endl;
        std::cout << (*row_it)[1] << std::endl;
        ++row_it;
    }
}

/*
    1. check tokens in a node is split into two tokens
*/
void check_split_tokens(std::vector<std::vector<std::string>> &nodes, bool db)
{
    std::vector<std::vector<std::string>>::iterator row_it = nodes.begin();
    std::vector<std::vector<std::string>>::iterator row_end = nodes.end();

    size_t line_num = 1;
    while (row_it!=row_end)
    {
        if (row_it->size()!=2)
        {
            if (db)
                throw std::runtime_error("DB: Invalid line format: " + std::to_string(line_num));
            throw std::runtime_error("Invalid line format: " + std::to_string(line_num));
        }
        ++line_num;
        ++row_it;
    }
}

std::vector<std::vector<std::string>> csv_parser(std::ifstream &file_stream, const char delim)
{
    // parse DB file
    std::vector<std::vector<std::string>> nodes;
    std::string line;

    while (std::getline(file_stream, line))
    {
        std::vector<std::string> tokens = split_line(line, delim);
        nodes.push_back(tokens);
    }
    check_split_tokens(nodes);
    return (nodes);
}

void trim_spaces_from_input(std::vector<std::vector<std::string>> &nodes)
{
    std::vector<std::vector<std::string>>::iterator row_it = nodes.begin();
    std::vector<std::vector<std::string>>::iterator row_end = nodes.end();

    size_t line_num = 1;
    while (row_it!=row_end)
    {
        if ((*row_it)[0].empty() || (*row_it)[1].empty())
            throw std::runtime_error("Invalid line format");
        size_t len = (*row_it)[0].length();
        // date' '|' 'value
        if ((*row_it)[0][len-1]!=' ' || (*row_it)[1][0]!=' ')
          throw std::runtime_error("Invalid line format: " + std::to_string(line_num));
        (*row_it)[0].erase(len-1, 1);
        (*row_it)[1].erase(0,1);
        ++line_num;
        ++row_it;
    }
}

bool check_dd_range(int dd, int mm, int yyyy)
{
    int thirty_first[] = {1,3,5,7,8,10,12,-1};
    int thirty[] = {4,6,9,11,-1};

    if (mm==2)
    {
        bool leap_year = ((yyyy%4==0 && yyyy%100!=0) || yyyy%400==0);
        if (leap_year)
        {
            if (!(1<=dd && dd<=29))
                return (false);
        }
        else
        {
            if (!(1<=dd && dd<=28))
                return (false);
        }
        return (true);
    }
    for (int idx=0;thirty_first[idx]!=-1;++idx)
    {
        if (mm==thirty_first[idx])
        {
            if (!(1<=dd && dd<=31))
                return (false);  
            return (true);
        }
    }
    for (int idx=0;thirty[idx]!=-1;++idx)
    {
        if (mm==thirty_first[idx])
        {
            if (!(1<=dd && dd<=30))
                return (false);  
            return (true);
        }  
    }
    return (true);
}

bool check_date_format(std::vector<std::vector<std::string>>::const_iterator row_it, int line_num)
{
    std::vector<std::string>::const_iterator col_it = (*row_it).begin();

    if ((*col_it).length() != 10)
        throw std::runtime_error("DB: Invalid Format: " + std::to_string(line_num));
    int i=0;
    for (;i<4;++i)
    {
        if (!std::isdigit((*col_it)[i]))
            throw std::runtime_error("DB: Invalid Format: " + std::to_string(line_num));
    }
    if ((*col_it)[i++]!='-')
        throw std::runtime_error("DB: Invalid Format: " + std::to_string(line_num));
    for (;i<7;++i)
    {
        if (!std::isdigit((*col_it)[i]))
            throw std::runtime_error("DB: Invalid Format: " + std::to_string(line_num));     
    }
    if ((*col_it)[i++]!='-')
        throw std::runtime_error("DB: Invalid Format: " + std::to_string(line_num));
    for (;i<10;++i)
    {
        if (!std::isdigit((*col_it)[i]))
            throw std::runtime_error("DB: Invalid Format: " + std::to_string(line_num));              
    }

    int yyyy = 0;
    int mm = 0;
    int dd = 0;

    i = 0;
    for (;i<4;++i)
    {
        yyyy = yyyy*10 + (*col_it)[i];
    }
    if (!(0<yyyy && yyyy<=2030))
        throw std::runtime_error("Invalid Format: " + std::to_string(line_num));
    i++;
    for (;i<7;++i)
    {
        mm = mm * 10 + (*col_it)[i];
    }
    if (!(1<=mm && mm<=12))
        throw std::runtime_error("Invalid Format: " + std::to_string(line_num));
    i++;
    for (;i<10;++i)
    {
        dd = dd * 10 + (*col_it)[i];
    }
    if (!check_dd_range(dd, mm, yyyy))
        throw std::runtime_error("Invalid Format: " + std::to_string(line_num));
}

//date validation
/*
    1. the length : 2000-01-01 = 10
    2. check [four digits] [-] [two digits] [-] [two digits]
    3. get yyyy[four digits] (skip++) mm[two digits] (skip++) dd[two digits]
    4. check the range of year, mon, and day.
*/
void check_db_format(std::vector<std::vector<std::string>> &nodes)
{
    std::vector<std::vector<std::string>>::const_iterator row_it = nodes.begin();
    std::vector<std::vector<std::string>>::const_iterator row_end = nodes.end();

    int line_num = 0;
    while (row_it!=row_end)
    {        
        ++row_it;
    }
}

struct s_date_val
{
    int error;
    std::string err_msg;
    std::vector<std::vector<std::string>> node;
};

int main(int argc, char *argv[])
{
    if (argc != 2)
        return (1);

    std::ifstream db_file_stream("data.csv", std::ios_base::in);
    std::ifstream input_file_stream(argv[1], std::ios_base::in);
    
    db_file_stream.exceptions(std::ios_base::badbit);
    input_file_stream.exceptions(std::ios_base::badbit);

    try {
        check_fstream_open(db_file_stream);
        check_fstream_open(input_file_stream);
        check_csv_file(db_file_stream,"date,exchange_rate", true);
        check_csv_file(input_file_stream,"date | value", false);

        std::vector<std::vector<std::string>> db_nodes = csv_parser(db_file_stream, ',');
        std::vector<std::vector<std::string>> input_nodes = csv_parser(input_file_stream, '|');
        
        trim_spaces_from_input(input_nodes);
        // print_tokens(input_nodes);

        //date validation
        /*
            1. the length : 2000-01-01 = 10
            2. check [four digits] [-] [two digits] [-] [two digits]
            3. get yyyy[four digits] (skip++) mm[two digits] (skip++) dd[two digits]
            4. check the range of year, mon, and day.
        */
        //DB should be the perfect status
        check_date_format(db_nodes);
        //value validation
        /*
            1. try the convertion to float
            2. check the sign of the converted value
        */
        
    } catch(std::exception &e){
        std::cout << e.what() << std::endl;
        return (1);
    }
        
    // select date and return the exchange rate

    // calculate the index value

    // print the index value

    return(0);
}
