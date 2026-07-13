#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

void check_csv_file(std::ifstream &file_stream, std::string format)
{
    // check the first line of csv
    std::string line;
    if (std::getline(file_stream, line))
    {
        if (line!=format)
        {
            throw std::runtime_error("invalid format of CSV.");
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
void check_split_tokens(std::vector<std::vector<std::string>> &nodes)
{
    std::vector<std::vector<std::string>>::iterator row_it = nodes.begin();
    std::vector<std::vector<std::string>>::iterator row_end = nodes.end();

    while (row_it!=row_end)
    {
        if (row_it->size()!=2)
            throw std::runtime_error("Invalid line format");
        ++row_it;
    }
}

std::vector<std::vector<std::string>> parser(std::ifstream &file_stream, const char delim)
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

    while (row_it!=row_end)
    {
        if ((*row_it)[0].empty() || (*row_it)[1].empty())
            throw std::runtime_error("Invalid line format");
        size_t len = (*row_it)[0].length();
        // date' '|' 'value
        if ((*row_it)[0][len-1]!=' ' || (*row_it)[1][0]!=' ')
          throw std::runtime_error("Invalid line format");
        (*row_it)[0].erase(len-1, 1);
        (*row_it)[1].erase(0,1);
        ++row_it;
    }
}

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
        check_csv_file(db_file_stream,"date,exchange_rate");
        check_csv_file(input_file_stream,"date | value");

        std::vector<std::vector<std::string>> db_nodes = parser(db_file_stream, ',');
        std::vector<std::vector<std::string>> input_nodes = parser(input_file_stream, '|');
        
        trim_spaces_from_input(input_nodes);
        // print_tokens(input_nodes);


    } catch(std::exception &e){
        std::cout << e.what() << std::endl;
        return (1);
    }

    // run parser

    // select date and return the exchange rate

    // calculate the index value

    // print the index value

    return(0);
}
