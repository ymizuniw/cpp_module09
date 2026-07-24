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
    IdxValue();
    IdxValue(const IdxValue &other);
    IdxValue &operator=(const IdxValue &other);
    bool operator<(const IdxValue &other) const;
    bool operator<(const IdxValue &other);
};

struct IdxPair{
    int large_idx;
    int small_idx;
    IdxPair();
    IdxPair(const IdxValue &other);
    IdxPair &operator=(const IdxPair &other);
};

IdxValue::IdxValue()
{
    this->idx = -1;
    this->value = -1;
}

IdxValue::IdxValue(const IdxValue &other): idx(other.idx), value(other.value)
{
    if (this==&other)
        return ;
    this->idx = other.idx;
    this->value = other.value;
}

IdxValue &IdxValue::operator=(const IdxValue &other)
{
    if (this==&other)
        return ;
    this->idx = other.idx;
    this->value = other.value;
}

bool IdxValue::operator<(const IdxValue &other) const
{
    if (this->value<other.value)
        return (true);
    return (false);
}

bool IdxValue::operator<(const IdxValue &other)
{
    if (this->value<other.value)
        return (true);
    return (false);
}

void Paring(std::deque<IdxValue> const &data, std::deque<IdxValue> &main_chain, std::deque<IdxValue> &pend_chain, std::deque<IdxPair> &idx_pair)
{
    // split data into main_chain and pend_chain keeping the idx of the values
    size_t size = data.size()/2;

    size_t pair_idx = 0;
    size_t data_idx = 0;
    IdxValue large_value = IdxValue();
    IdxValue small_value = IdxValue();
    IdxPair idx_pair_tmp = IdxPair();

    while (pair_idx<size)
    {
        if (data[data_idx]<data[data_idx+1])
        {
            large_value = data[data_idx+1];
            small_value = data[data_idx];
            idx_pair_tmp.large_idx = data[data_idx+1].idx;
            idx_pair_tmp.small_idx = data[data_idx].idx;
        }
        else
        {
            large_value = data[data_idx];
            small_value = data[data_idx+1];
            idx_pair_tmp.large_idx = data[data_idx].idx;
            idx_pair_tmp.small_idx = data[data_idx+1].idx;
        }
        main_chain.push_back(large_value);
        pend_chain.push_back(small_value);
        idx_pair.push_back(idx_pair_tmp);
        ++pair_idx;
        data_idx += 2;
    }
}

void Insertion(std::deque<IdxValue> &sorted_main_chain, std::deque<IdxValue> &pend_chain, std::deque<IdxPair> &idx_pair)
{
    // here, pend_chain elements would be inserted into sorted_main_chain, 
    // but the idx_pair can be lacking for the last element in pend_chain,
    // and the element cannot be searched by the upper limit of the corresponding element in the sorted_main_chain

    bool odd = (pend_chain.size()%2!=0);

    // from begin() to specific_idx::iterator : paired element

    // from begin() to end() : remaining element

}

std::deque<IdxValue> FordJohnson(std::deque<IdxValue> const &data)
{
    std::deque<IdxValue> main_chain;
    std::deque<IdxValue> pend_chain;
    std::deque<IdxPair> idx_pair;

    // keep remaining data if odd ocunt
    IdxValue remain = IdxValue();
    if (data.size()%2!=0)
    {
        remain = data[data.size()-1];
    }

    // Pairing()
    Paring(data, main_chain, pend_chain, idx_pair);

    std::deque<IdxValue> sorted_main_chain = FordJohnson(main_chain);

    if (data.size()%2!=0)
    {
        pend_chain.push_back(remain);
    }

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
