# ifndef PAIR_INDEX_HPP
# define PAIR_INDEX_HPP

# include <deque>

struct IdxPair {
    int large;
    int small;
    IdxPair(int large_idx, int small_idx);
};

class PairIndex {
    private:
        std::deque<IdxPair> pairs_;
    public:
        PairIndex();
        PairIndex(const PairIndex &other);
        PairIndex &operator=(const PairIndex &other);
        ~PairIndex();

        void add(int main_chain_idx, int pend_idx);
        int getPendIdxOf(int main_chain_idx) const;
        int getMainChainIdxOf(int pend_idx) const;
};

# endif
