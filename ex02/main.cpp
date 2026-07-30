# include "FordJohnson.hpp"
# include <iostream>
# include <sstream>
# include <stdexcept>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <list of integers>" << std::endl;
        return (1);
    }
    try{
        std::deque<IdxValue> data;

        for (size_t i = 1; i < static_cast<size_t>(argc); i++)
        {
            int tmp;
            std::stringstream ss;
            ss << argv[i];
            ss >> tmp;
            if (ss.fail())
                throw std::invalid_argument("Error: not a valid integer: " + std::string(argv[i]));
            if (tmp<0)
                throw std::invalid_argument("Error: negative number not allowed");
            data.push_back(IdxValue(i-1,tmp));
        }

        std::cout << "Before: ";
        for (std::deque<IdxValue>::const_iterator it = data.begin(); it != data.end(); ++it)
            std::cout << (*it).value << " ";
        std::cout << std::endl;

        FordJohnson<std::deque> deque_fj(data);
        std::deque<IdxValue> sorted_deque = deque_fj.sort();

        std::cout << "After: ";
        for (std::deque<IdxValue>::const_iterator it = sorted_deque.begin(); it != sorted_deque.end(); ++it)
            std::cout << (*it).value << " ";
        std::cout << std::endl;
    } catch(const std::exception &e){
        std::cout << e.what() << std::endl;
    }
    return (0);
}
