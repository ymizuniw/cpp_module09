# include "PairIndex.hpp"

IdxPair::IdxPair(int large_idx, int small_idx): large(large_idx), small(small_idx) {}

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
        return (*this);
    pairs_=other.pairs_;
    return (*this);
}

PairIndex::~PairIndex(){}

//PairIndex class functions
void PairIndex::add(int large_idx, int small_idx)
{
    pairs_.push_back(IdxPair(large_idx, small_idx));
}

int  PairIndex::getSmallIdxOf(int large_idx) const
{
    std::deque<IdxPair>::const_iterator it = pairs_.begin();
    std::deque<IdxPair>::const_iterator end_it = pairs_.end();

    while (it!=end_it)
    {
        if ((*it).large==large_idx)
        {
            return ((*it).small);
        }
        ++it;
    }
    throw std::exception();
}

// this will get the place of the main_chain element that is target place for pend element to insert.
int  PairIndex::getLargeIdxOf(int pend_idx) const
{
    std::deque<IdxPair>::const_iterator it = pairs_.begin();
    std::deque<IdxPair>::const_iterator end_it = pairs_.end();

    while (it!=end_it)
    {
        if ((*it).small==pend_idx)
        {
            return ((*it).large);// in case of odd remaining elem, then it will return REMAINING_ELEM(-2).
        }
        ++it;
    }
    return (-1);
}
