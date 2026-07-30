# include "FordJohnson.hpp"

template<typename Container>
FordJohnson<Container>::FordJohnson(): idx_pair_() {}

template<typename Container>
FordJohnson<Container>::FordJohnson(Container const &data)
{
    data_=data;
}

template<typename Container>
FordJohnson<Container>::FordJohnson(const FordJohnson &other)
{
    if (this==&other)
        return ;

    data_=other.data_;
    main_chain_=other.main_chain_;
    pend_=other.pend_;
    idx_pair_=other.idx_pair_;
}

template<typename Container>
FordJohnson<Container> &FordJohnson<Container>::operator=(const FordJohnson<Container> &other)
{
    if (this==&other)
        return (*this);
    
    data_=other.data_;
    main_chain_=other.main_chain_;
    pend_=other.pend_;
    idx_pair_=other.idx_pair_;

    return (*this);
}

template<typename Container>
FordJohnson<Container>::~FordJohnson() {}

// In main_chain, search the IdxValue object its idx variable has unique_idx given as an argument.
template<typename Container>
IdxValue FordJohnson<Container>::getIdxValueOfMainChain(int unique_idx)
{
    typename Container::const_iterator it = main_chain_.begin();
    typename Container::const_iterator end_it = main_chain_.end();

    while (it!=end_it)
    {
        if ((*it).unique_idx==unique_idx)
        {
            return (*it);
        }
        ++it;
    }
    throw std::exception();
}

// In pend, search the IdxValue object its idx variable has unique_idx given as an argument.
template<typename Container>
IdxValue FordJohnson<Container>::getIdxValueOfPend(int unique_idx)
{
    typename Container::const_iterator it = pend_.begin();
    typename Container::const_iterator end_it = pend_.end();

    while (it!=end_it)
    {
        if ((*it).unique_idx==unique_idx)
        {
            return (*it);
        }
        ++it;
    }
    throw std::exception();
}

template<typename Container>
int      FordJohnson<Container>::getPositionOfMainChain(int unique_idx)
{
    typename Container::const_iterator it = main_chain_.begin();
    typename Container::const_iterator end_it = main_chain_.end();

    size_t pos = 0;
    while (it!=end_it)
    {
        if ((*it).unique_idx==unique_idx)
        {
            return (pos);
        }
        pos++;
        ++it;
    }
    throw std::exception();
}

template<typename Container>
void FordJohnson<Container>::pairing()
{
    IdxValue remain;
    bool odd = false;

    if (data_.size()%2!=0)
    {
        remain = data_.back();
        data_.erase(data_.end()-1);
        odd = true;
    }

    typename Container::const_iterator it = data_.begin();
    typename Container::const_iterator end_it = data_.end();

    while (it!=end_it)
    {
        IdxValue large_idx_value;
        IdxValue small_idx_value;
        int large_idx = -1;
        int small_idx = -1;

        if ((*it)<(*(it+1)))
        {
            large_idx_value = (*(it+1));
            small_idx_value = (*it);
            large_idx = (*(it+1)).unique_idx;
            small_idx = (*it).unique_idx;
        }
        else
        {
            large_idx_value = (*it);
            small_idx_value = (*(it+1));
            large_idx = (*it).unique_idx;
            small_idx = (*(it+1)).unique_idx;
        }
        main_chain_.push_back(large_idx_value);
        pend_.push_back(small_idx_value);
        idx_pair_.add(large_idx, small_idx);
        it += 2;
    }
    if (odd)
    {
        pend_.push_back(remain);
        idx_pair_.add(REMAINING_ELEM, remain.unique_idx);
        data_.push_back(remain);
    }
}

template<typename Container>
void FordJohnson<Container>::sortPend()
{
    std::deque<IdxValue> sorted_pend;
   
    typename Container::const_iterator it = main_chain_.begin();
    typename Container::const_iterator end_it = main_chain_.end();
   int pend_unique_idx;

   while (it!=end_it)
   {
    pend_unique_idx = idx_pair_.getSmallIdxOf((*it).unique_idx);
    sorted_pend.push_back(getIdxValueOfPend(pend_unique_idx));
    ++it;
   }
   if (data_.size()%2!=0)
   {
    sorted_pend.push_back(pend_.back());
   }
   pend_ = sorted_pend;
}

template<typename Container>
int FordJohnson<Container>::getSpaceSize(typename Container::const_iterator &pend_it)
{
    int pos = idx_pair_.getLargeIdxOf((*pend_it).unique_idx);
    if (pos==REMAINING_ELEM)
        return (main_chain_.size());
    return (getPositionOfMainChain(pos)+1);
}

template<typename Container>
void FordJohnson<Container>::insertByJacobsthal()
{
    int k = 1;
    typename Container::const_iterator pend_it = pend_.cbegin() + 1;
    typename Container::const_iterator pend_end_it = pend_.cend();

    typename Container::const_iterator start_it;
    typename Container::const_iterator end_it;

    while (pend_it!=pend_end_it)
    {
        int space_size_ulimit = (1<<(k+1)) - 1;
        int space_size = getSpaceSize(pend_it);
        start_it = pend_it;

        while (space_size<space_size_ulimit)
        {
            ++pend_it;
            if (pend_it==pend_end_it)
                break ;
            space_size = getSpaceSize(pend_it);
        }
        if (pend_it!=pend_end_it)
            ++pend_it;
        end_it = pend_it;

        typename Container::const_iterator main_chain_upper_it = main_chain_.cbegin() + space_size;
        while (start_it!=end_it)
        {
            typename Container::const_iterator upper_bound_it = std::upper_bound(main_chain_.cbegin(), main_chain_upper_it, *(end_it-1));
            main_chain_.insert(upper_bound_it, *(end_it-1));
            --end_it;
        }
        ++k;
    }
}

template<typename Container>
void FordJohnson<Container>::insertion()
{
    int main_chain_key = main_chain_[0].unique_idx;
    int pend_uidx = idx_pair_.getSmallIdxOf(main_chain_key);

    IdxValue pend_elem = getIdxValueOfPend(pend_uidx);
    main_chain_.insert(main_chain_.cbegin(), pend_elem);
    if (pend_.size()==1)
        return ;
    insertByJacobsthal();
}

template<typename Container>
Container FordJohnson<Container>::sort()
{
    if (data_.size()==1)
    {
        main_chain_.push_back(data_.back());
        return (main_chain_);
    }
    pairing();
    FordJohnson recursive_fj(main_chain_);
    main_chain_ = recursive_fj.sort();
    sortPend();
    insertion();
    return (main_chain_);
}
