# include "FordJohnson.hpp"

template<template<typename T, typename Allocator = std::allocator<T> > class Container>
FordJohnson<Container>::FordJohnson(): idx_pair_() {}

template<template<typename T, typename Allocator = std::allocator<T> > class Container>
FordJohnson<Container>::FordJohnson(Container<IdxValue> const &data)
{
    data_=data;
}

template<template<typename T, typename Allocator = std::allocator<T> > class Container>
FordJohnson<Container>::FordJohnson(const FordJohnson &other)
{
    if (this==&other)
        return ;

    data_=other.data_;
    main_chain_=other.main_chain_;
    pend_=other.pend_;
    idx_pair_=other.idx_pair_;
}

template<template<typename T, typename Allocator = std::allocator<T> > class Container>
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

template<template<typename T, typename Allocator = std::allocator<T> > class Container>
FordJohnson<Container>::~FordJohnson() {}

// In main_chain, search the IdxValue object its idx variable has unique_idx given as an argument.
template<template<typename T, typename Allocator = std::allocator<T> > class Container>
IdxValue FordJohnson<Container>::getIdxValueOfMainChain(int unique_idx)
{
    typename Container<IdxValue>::const_iterator it = main_chain_.begin();
    typename Container<IdxValue>::const_iterator end_it = main_chain_.end();

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
template<template<typename T, typename Allocator = std::allocator<T> > class Container>
IdxValue FordJohnson<Container>::getIdxValueOfPend(int unique_idx)
{
    typename Container<IdxValue>::const_iterator it = pend_.begin();
    typename Container<IdxValue>::const_iterator end_it = pend_.end();

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

template<template<typename T, typename Allocator = std::allocator<T> > class Container>
int      FordJohnson<Container>::getPositionOfMainChain(int unique_idx)
{
    typename Container<IdxValue>::const_iterator it = main_chain_.begin();
    typename Container<IdxValue>::const_iterator end_it = main_chain_.end();

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

template<template<typename T, typename Allocator = std::allocator<T> > class Container>
void FordJohnson<Container>::pairing()
{
    IdxValue remain;
    bool odd = false;

    if (data_.size()%2!=0)
    {
        remain = data_.back();
        data_.erase(std::prev(data_.end()));
        odd = true;
    }

    typename Container<IdxValue>::const_iterator it = data_.begin();
    typename Container<IdxValue>::const_iterator end_it = data_.end();

    while (it!=end_it)
    {
        IdxValue large_idx_value;
        IdxValue small_idx_value;
        int large_idx = -1;
        int small_idx = -1;

        if ((*it)<(*std::next(it)))
        {
            large_idx_value = (*std::next(it));
            small_idx_value = (*it);
            large_idx = (*std::next(it)).unique_idx;
            small_idx = (*it).unique_idx;
        }
        else
        {
            large_idx_value = (*it);
            small_idx_value = (*std::next(it));
            large_idx = (*it).unique_idx;
            small_idx = (*std::next(it)).unique_idx;
        }
        main_chain_.push_back(large_idx_value);
        pend_.push_back(small_idx_value);
        idx_pair_.add(large_idx, small_idx);
        it = std::next(it,2);
    }
    if (odd)
    {
        pend_.push_back(remain);
        idx_pair_.add(REMAINING_ELEM, remain.unique_idx);
        data_.push_back(remain);
    }
}

template<template<typename T, typename Allocator = std::allocator<T> > class Container>
void FordJohnson<Container>::sortPend()
{
    Container<IdxValue> sorted_pend;

    typename Container<IdxValue>::const_iterator it = main_chain_.begin();
    typename Container<IdxValue>::const_iterator end_it = main_chain_.end();
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

template<template<typename T, typename Allocator = std::allocator<T> > class Container>
int FordJohnson<Container>::getSpaceSize(typename Container<IdxValue>::const_iterator &pend_it)
{
    int pos = idx_pair_.getLargeIdxOf((*pend_it).unique_idx);
    if (pos==REMAINING_ELEM)
        return (main_chain_.size());
    return (getPositionOfMainChain(pos)+1);
}

template<template<typename T, typename Allocator = std::allocator<T> > class Container>
void FordJohnson<Container>::insertByJacobsthal()
{
    int k = 1;
    typename Container<IdxValue>::const_iterator pend_it = std::next(pend_.cbegin());
    typename Container<IdxValue>::const_iterator pend_end_it = pend_.cend();

    typename Container<IdxValue>::const_iterator start_it;
    typename Container<IdxValue>::const_iterator end_it;

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

        typename Container<IdxValue>::const_iterator main_chain_upper_it = std::next(main_chain_.cbegin(),space_size);
        while (start_it!=end_it)
        {
            typename Container<IdxValue>::const_iterator upper_bound_it = std::upper_bound(main_chain_.cbegin(), main_chain_upper_it, *std::prev(end_it));
            main_chain_.insert(upper_bound_it, *std::prev(end_it));
            --end_it;
        }
        ++k;
    }
}

template<template<typename T, typename Allocator = std::allocator<T> > class Container>
void FordJohnson<Container>::insertion()
{
    int main_chain_key = main_chain_.front().unique_idx;
    int pend_uidx = idx_pair_.getSmallIdxOf(main_chain_key);

    IdxValue pend_elem = getIdxValueOfPend(pend_uidx);
    main_chain_.insert(main_chain_.cbegin(), pend_elem);
    if (pend_.size()==1)
        return ;
    insertByJacobsthal();
}

template<template<typename T, typename Allocator = std::allocator<T> > class Container>
Container<IdxValue> FordJohnson<Container>::sort()
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
