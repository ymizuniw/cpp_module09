# ifndef FORDJOHNSON_HPP
# define FORDJOHNSON_HPP

# include <deque>
# include <algorithm>

# include "IdxValue.hpp"
# include "PairIndex.hpp"

#define REMAINING_ELEM -2

// FordJohnson class receives deque<IdxValue> as an argument, and sort it.
class FordJohnson {
    private:
        std::deque<IdxValue> data_;
        std::deque<IdxValue> main_chain_;
        std::deque<IdxValue> pend_;
        PairIndex idx_pair_;

        IdxValue getIdxValueOfMainChain(int unique_idx);
        IdxValue getIdxValueOfPend(int);
        int      getPositionOfMainChain(int unique_idx);
        void pairing();
        void sortPend();
        void insertion();

    public:
        FordJohnson();
        FordJohnson(std::deque<IdxValue> const &data);
        FordJohnson(const FordJohnson &other);
        FordJohnson &operator=(const FordJohnson &other);
        ~FordJohnson();
        std::deque<IdxValue> sort();
};

# endif
