# include "FordJohnson.hpp"
# include <iostream>
# include <sstream>
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

        for (int i = 1; i < argc; i++)
        {
            std::stringstream ss;
            int tmp;
            ss << argv[i];
            ss >> tmp;
            data.push_back(IdxValue(i-1,tmp));
        }
        FordJohnson fj(data);
        std::deque<IdxValue> sorted_data = fj.sort();
        // for (int i=0;i<argc-1;i++)
        // {
        //     std::cout << sorted_data[i].value << std::endl;
        // }
    } catch(const std::exception &e){
        std::cout << e.what() << std::endl;
    }
    return (0);
}
