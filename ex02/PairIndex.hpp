#ifndef PAIR_INDEX_HPP
#define PAIR_INDEX_HPP

#include <memory>

struct IdxPair {
    int large;
    int small;
    IdxPair(int large_idx, int small_idx);
};

template <template <typename T, typename Allocator = std::allocator<T> > class Container>
class PairIndex
{
  private:
    Container<IdxPair> pairs_;

  public:
    PairIndex();
    PairIndex(const PairIndex& other);
    PairIndex& operator=(const PairIndex& other);
    ~PairIndex();

    void add(int main_chain_idx, int pend_idx);
    int getSmallIdxOf(int main_chain_idx) const;
    int getLargeIdxOf(int pend_idx);
};

#include "PairIndex.tpp"

#endif
