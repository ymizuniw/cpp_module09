# include "FordJohnson.hpp"
# include <iostream>
# include <sstream>
# include <stdexcept>
/*
    PROGRAM: PmergeMe
    INPUT:  ./PmergeMe 3 5 9 7 4
    DATA STRUCTURE: std::deque<int>
    LOGIC:
        
*/ 

/*
    map<int, int> : index and value
    1. sort the larger group recursively
    2. insert the smallest pair's partner by serching the partner's index in the map
    3. incert the remaining elements in the order of Jacobsthal numbers by binary search in the sorted larger group.
*/

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
        FordJohnson<std::deque> fj(data);
        std::deque<IdxValue> sorted_data = fj.sort();
        for (int i=0;i<argc-1;i++)
        {
            std::cout << sorted_data[i].value << std::endl;
        }
    } catch(const std::exception &e){
        std::cout << e.what() << std::endl;
    }
    return (0);
}

// # include <list>
// int main(int argc, char *argv[])
// {
//     if (argc < 2)
//     {
//         std::cerr << "Usage: " << argv[0] << " <list of integers>" << std::endl;
//         return (1);
//     }
//     try{
//         std::list<IdxValue> data;

//         for (size_t i = 1; i < static_cast<size_t>(argc); i++)
//         {
//             int tmp;
//             std::stringstream ss;
//             ss.exceptions(std::ios::failbit | std::ios::badbit);
//             ss << argv[i];
//             ss >> tmp;
//             if (tmp<0)
//                 throw std::exception();
//             data.push_back(IdxValue(i-1,tmp));
//         }
//         FordJohnson<std::list<IdxValue> > fj(data);
//         std::list<IdxValue> sorted_data = fj.sort();

//         std::list<IdxValue>::const_iterator it = sorted_data.cbegin();
//         std::list<IdxValue>::const_iterator it_end = sorted_data.cend();    
//         while (it!=it_end)
//         {
//             std::cout << (*it).value << std::endl;
//             ++it;
//         }

//     } catch(const std::exception &e){
//         std::cout << e.what() << std::endl;
//     }
//     return (0);
// }
