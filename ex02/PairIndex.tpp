#include "PairIndex.hpp"

inline IdxPair::IdxPair(int large_idx, int small_idx) : large(large_idx), small(small_idx) {}

template <template <typename T, typename Allocator = std::allocator<T> > class Container>
PairIndex<Container>::PairIndex()
{
}

template <template <typename T, typename Allocator = std::allocator<T> > class Container>
PairIndex<Container>::PairIndex(const PairIndex& other)
{
    if (this == &other)
        return;
    pairs_ = other.pairs_;
}

template <template <typename T, typename Allocator = std::allocator<T> > class Container>
PairIndex<Container>& PairIndex<Container>::operator=(const PairIndex& other)
{
    if (this == &other)
        return (*this);
    pairs_ = other.pairs_;
    return (*this);
}

template <template <typename T, typename Allocator = std::allocator<T> > class Container>
PairIndex<Container>::~PairIndex()
{
}

// PairIndex class functions
template <template <typename T, typename Allocator = std::allocator<T> > class Container>
void PairIndex<Container>::add(int large_idx, int small_idx)
{
    pairs_.push_back(IdxPair(large_idx, small_idx));
}

template <template <typename T, typename Allocator = std::allocator<T> > class Container>
int PairIndex<Container>::getSmallIdxOf(int large_idx) const
{
    typename Container<IdxPair>::const_iterator it = pairs_.begin();
    typename Container<IdxPair>::const_iterator end_it = pairs_.end();

    while (it != end_it) {
        if ((*it).large == large_idx) {
            return ((*it).small);
        }
        ++it;
    }
    throw std::exception();
}

// this will get the place of the main_chain element that is target place for pend element to
// insert.
template <template <typename T, typename Allocator = std::allocator<T> > class Container>
int PairIndex<Container>::getLargeIdxOf(int pend_idx)
{
    typename Container<IdxPair>::iterator it = pairs_.begin();
    typename Container<IdxPair>::iterator end_it = pairs_.end();

    while (it != end_it) {
        if ((*it).small == pend_idx) {
            return ((*it).large); // in case of odd remaining elem, then it will return
                                  // REMAINING_ELEM(-2).
        }
        ++it;
    }
    return (-1);
}
