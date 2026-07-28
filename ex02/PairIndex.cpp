# include "PairIndex.hpp"

PairIndex::PairIndex() {}

PairIndex::PairIndex(const PairIndex &other)
{
    if (this==&other)
        return ;
    pairs_=other.pairs_;
}

PairIndex &PairIndex::operator=(const PairIndex &other)
{
    if (this==&other)
        return ;
    pairs_=other.pairs_;
}

PairIndex::~PairIndex(){}

//PairIndex class functions
void PairIndex::add(int large_idx, int small_idx)
{
    pairs_.push_back(IdxPair(large_idx, small_idx));
}

// this function will be used???
int  PairIndex::getPendIdxOf(int main_chain_idx) const
{
    std::deque<IdxPair>::const_iterator it = pairs_.begin();
    std::deque<IdxPair>::const_iterator end_it = pairs_.end();

    while (it!=end_it)
    {
        if ((*it).large==main_chain_idx)
        {
            return ((*it).small);
        }
        ++it;
    }
    throw std::exception();
}

// this will get the place of the main_chain element that is target place for pend element to insert.
int  PairIndex::getMainChainIdxOf(int pend_idx) const
{
    std::deque<IdxPair>::const_iterator it = pairs_.begin();
    std::deque<IdxPair>::const_iterator end_it = pairs_.end();

    size_t main_chain_idx = 0;
    while (it!=end_it)
    {
        if ((*it).small==pend_idx)
        {
            return (main_chain_idx);// in case of odd remaining elem, then it will return REMAINING_ELEM(-2).
        }
        main_chain_idx++;
        ++it;
    }
    return (-1);
}
