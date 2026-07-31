#ifndef FORDJOHNSON_HPP
#define FORDJOHNSON_HPP

#include "IdxValue.hpp"
#include "PairIndex.hpp"
#include <memory>

#define REMAINING_ELEM -2

template <template <typename T, typename Allocator = std::allocator<T> > class Container>
class FordJohnson
{
  private:
    Container<IdxValue> data_;
    Container<IdxValue> main_chain_;
    Container<IdxValue> pend_;
    PairIndex<Container> idx_pair_;

    IdxValue getIdxValueOfMainChain(int unique_idx);
    IdxValue getIdxValueOfPend(int unique_idx);
    int getPositionOfMainChain(int unique_idx);
    void pairing();
    void sortPend();
    void insertion();
    void insertByJacobsthal();
    int getSpaceSize(typename Container<IdxValue>::iterator& pend_it);

  public:
    FordJohnson();
    FordJohnson(Container<IdxValue> const& data);
    FordJohnson(const FordJohnson& other);
    FordJohnson& operator=(const FordJohnson& other);
    ~FordJohnson();
    Container<IdxValue> sort();
};

#include "FordJohnson.tpp"

#endif
