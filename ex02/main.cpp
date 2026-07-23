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

struct IdxValue
{
    int idx;
    int val;
};

/*
    std::deque<IdxValue> data;

*/

std::deque<IdxValue> merge_insertion(std::deque<IdxValue> data)
{
    /*
        pairing data
        merge_insertion to main chain
        binary insertion in the order of jacobian
    */
   /*
        1. how to pair the data and keep the idx?
            construct a new deque<IdxValue> "main_chain" its size if half of the original data, 
        and push (and pop() to delete it correctly) the contents of the argument (deque<IdxValue>)data's
        elements to it after the comparison between suceeding ones.
   */

   /*
        2. call merge_insertion() that is passed the main_chain created at 1.,
            and get the main_chain sorted.
   */
    
   /*
        3. select one element in the pend_chain in the order of jacobian,
             search the main_chain element corresponding to the idx of the selected one,
              setting the upper limit of binary search to find the inserting place
                 to the index of the main_chain.
            repeat this till all the pend_chain elements are inserted.
   */

    /*
        if the size is odd, the remain = data[size-1];
        and handle this as the last element of the pending elements to the main_chain.
    */

    // binary insertion in the order of jacobian

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


    // // IdxValue up the elements
    // size_t size = (argc - 1);
    // bool odd = false;
    // IdxValue remain;
    // if (size % 2 != 0)
    // {
    //     odd = true;
    //     remain.idx = size - 1;
    //     remain.val = tmp[size - 1];
    //     --size;
    // }

    // IdxValue pairs[size/2];
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
