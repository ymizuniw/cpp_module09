# ifndef FORDJOHNSON_HPP
# define FORDJOHNSON_HPP

# include <deque>
# include <algorithm>

# include "IdxValue.hpp"
# include "PairIndex.hpp"

#define REMAINING_ELEM -2

template<typename Container>
class FordJohnson {
    private:
        Container data_;
        Container main_chain_;
        Container pend_;
        PairIndex idx_pair_;

        IdxValue getIdxValueOfMainChain(int unique_idx);
        IdxValue getIdxValueOfPend(int unique_idx);
        int      getPositionOfMainChain(int unique_idx);
        void pairing();
        void sortPend();
        void insertion();
        void insertByJacobsthal();
        int getSpaceSize(typename Container::const_iterator &pend_it);
    public:
        FordJohnson();
        FordJohnson(Container const &data);
        FordJohnson(const FordJohnson &other);
        FordJohnson &operator=(const FordJohnson &other);
        ~FordJohnson();
        Container sort();
};

# include "FordJohnson.tpp"

# endif
