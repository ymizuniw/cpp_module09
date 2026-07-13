#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

bool check_csv_file(std::ifstream &file_stream, std::string format)
{
    // check the first line of csv
    std::string line;
    if (std::getline(file_stream, line))
    {
        if (line!=format)
        {
            std::cerr << "invalid format of CSV." << std::endl;
            return (false);
        }
    }
    else
        return (false);
    return (true);
}

bool check_fstream_open(std::ifstream &file_stream)
{
    if (!file_stream.is_open()){
        return(false);
    }
    return (true);
}

// https://dexall.co.jp/articles/?p=2187#i-4
// in case of ",", it works. 
// in case of " | ", split by '|' and trimming spaces in the first and second substring.
std::vector<std::string> split_line(std::string &line, const char delim)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(line);

    while (std::getline(iss, token, delim))
    {
        // std::cout << token << std::endl;
        if (!token.empty()){
            tokens.push_back(token);
        }
    }
    return (tokens);
}

/*
    1. check tokens in a node is split into two tokens
*/
bool check_split_tokens(const std::vector<std::vector<std::string>> &nodes)
{
    std::vector<std::vector<std::string>>::const_iterator row_it = nodes.begin();
    std::vector<std::vector<std::string>>::const_iterator row_end = nodes.end();

    while (row_it!=row_end)
    {
        if (row_it->size()!=2)
            return (false);
        ++row_it;
    }
    return (true);
}

std::vector<std::vector<std::string>> parser(std::ifstream &db_file_stream, std::ifstream &input_file_stream)
{
    // parse DB file
    std::vector<std::vector<std::string>> nodes;
    std::string line;

    while (std::getline(db_file_stream, line))//\n?
    {
        std::vector<std::string> tokens = split_line(line, ',');
        nodes.push_back(tokens);
    }
    // check the std::basic_ios status
    if (db_file_stream.bad())
    {
        throw 
    }
    if (!check_split_tokens(nodes))
        return(false);
    return (true);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return (1);

    std::ifstream db_file_stream("data.csv", std::ios_base::in);
    std::ifstream input_file_stream(argv[1], std::ios_base::in);
    
    db_file_stream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
    input_file_stream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
    try {
        check_fstream_open(db_file_stream);
        check_fstream_open(input_file_stream);

        if (!check_csv_file(db_file_stream,"date,exchange_rate"))
            return (1);
        if (!check_csv_file(input_file_stream,"date | value"))
            return (1);  
    } catch(...){

    }

    // if (!check_fstream_open(db_file_stream))
    //     return (1);
    // if (!check_fstream_open(input_file_stream))
    //     return (1);

    // if (!check_csv_file(db_file_stream,"date,exchange_rate"))
    //     return (1);
    // if (!check_csv_file(input_file_stream,"date | value"))
    //     return (1);
    
    // run parser 
    
    // select date and return the exchange rate

    // calculate the index value

    // print the index value

    return(0);
}
