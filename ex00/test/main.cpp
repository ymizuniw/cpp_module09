#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

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

void print(std::string str)
{
    std::cout << str << std::endl;
}

int main(void)
{
    std::string str = "2009-01-02 | 0";

    std::vector<std::string> tokens = split_line(str, '|');

    std::vector<std::string>::iterator first = std::begin(tokens);
    std::vector<std::string>::iterator end = std::end(tokens);

    if (tokens.size()!=2)
    {
        std::cout << "line is split by into more/less than 2" << std::endl;
        return (1);
    }

    size_t count = 0;
    while (first!=end)
    {
        count++;
        // std::cout <<  count << " times called" << std::endl;
        print(*first);
        ++first;
    }
    return (0);
}
