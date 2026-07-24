#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <deque>
#include <map>

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

struct IdxValue{
    int idx;
    int value;
};

struct IdxPair{
    int large;
    int small;
};



std::deque<IdxValue> FordJohnson(std::deque<IdxValue> data)
{
    std::deque<IdxValue> main_chain;
    std::deque<IdxValue> pend_chain;
    std::deque<IdxPair> idx_pair;

    // Pairing()

    std::deque<IdxValue> sorted_main_chain = FordJohnson(main_chain);

    // Insertion()

    return (sorted_main_chain);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <list of integers>" << std::endl;
        return (1);
    }

    int tmp[argc - 1];
    for (int i = 1; i < argc; ++i)
    {
        tmp[i - 1] = 0;
    }
    for (int i = 1; i < argc; ++i)
    {
        tmp[i - 1] = std::atoi(argv[i]);
    }

    /*
        Distribute the tmp vals to container(deque as default)
    */

    // KeyValue up the elements
    // size_t size = (argc - 1);
    // bool odd = false;
    // KeyValue remain;
    // if (size % 2 != 0)
    // {
    //     odd = true;
    //     remain.idx = size - 1;
    //     remain.val = tmp[size - 1];
    //     --size;
    // }

    // KeyValue pairs[size/2];
    // for (size_t i=0;i<size/2;++i)
    // {
    //     pairs[i].large.idx = i;
    //     pairs[i].large.val = 0;
    //     pairs[i].small.idx = i;
    //     pairs[i].small.val = 0;
    // }

    // size_t tmp_idx = 0;
    // size_t pair_idx = 0;

    // while (pair_idx<size/2)
    // {
    //     pairs[pair_idx].large.idx = pair_idx;
    //     pairs[pair_idx].small.idx = pair_idx;
    //     size_t large = 0;
    //     size_t small = 0;

    //     if (tmp[tmp_idx]<tmp[tmp_idx+1])
    //     {
    //         std::cout << tmp[tmp_idx+1] << " is larger than " << tmp[tmp_idx] << std::endl; 
    //         large = tmp[tmp_idx+1];
    //         small = tmp[tmp_idx];
    //     }
    //     else
    //     {
    //         std::cout << tmp[tmp_idx] << " is larger than " << tmp[tmp_idx+1] << std::endl; 
    //         large = tmp[tmp_idx];
    //         small = tmp[tmp_idx+1];    
    //     }
    //     pairs[pair_idx].large.val = large;
    //     pairs[pair_idx].small.val = small;
    //     ++pair_idx;
    //     tmp_idx = tmp_idx + 2;
    // }
    // print_pairs(pairs, size/2);

    // Reccursively sort the larger group

    // Insert the smallest pair's partner

    // Insert the remaining elements in the order of Jacobsthal numbers

    return (0);
}
