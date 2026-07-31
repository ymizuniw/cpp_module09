# include "FordJohnson.hpp"
# include <iostream>
# include <sstream>
# include <stdexcept>
# include <list>
# include <deque>
# include <ctime>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <list of integers>" << std::endl;
        return (1);
    }
    try{
        std::deque<IdxValue> deq_data;
        std::list<IdxValue> list_data;
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
            deq_data.push_back(IdxValue(i-1,tmp));
            list_data.push_back(IdxValue(i-1,tmp));
        }

        std::cout << "Before: ";
        for (std::deque<IdxValue>::const_iterator it = deq_data.begin(); it != deq_data.end(); ++it)
            std::cout << (*it).value << " ";
        std::cout << std::endl;

        FordJohnson<std::deque> deque_fj(deq_data);
        clock_t deq_time = clock();
        std::deque<IdxValue> sorted_deque = deque_fj.sort();
        deq_time = clock() - deq_time;

        std::cout << "After: ";
        for (std::deque<IdxValue>::const_iterator it = sorted_deque.begin(); it != sorted_deque.end(); ++it)
            std::cout << (*it).value << " ";
        std::cout << std::endl;

        FordJohnson<std::list> list_fj(list_data);
        clock_t list_time = clock();
        std::list<IdxValue> sorted_list = list_fj.sort();
        list_time = clock() - list_time;

        std::cout << "Time to process a range of " << deq_data.size() << " elements with " << "std::deque<IdxValue> : " << deq_time << " us" << std::endl;
        std::cout << "Time to process a range of " << list_data.size() << " elements with " << "std::list<IdxValue> : " << list_time << " us" << std::endl;
    } catch(const std::exception &e){
        std::cout << e.what() << std::endl;
    }
    return (0);
}
