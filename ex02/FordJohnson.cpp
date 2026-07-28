# include "FordJohnson.hpp"

FordJohnson::FordJohnson(): idx_pair_() {}

FordJohnson::FordJohnson(const FordJohnson &other)
{
    if (this==&other)
        return ;

    data_=other.data_;
    main_chain_=other.main_chain_;
    pend_=other.pend_;
    idx_pair_=other.idx_pair_;
}

FordJohnson &FordJohnson::operator=(const FordJohnson &other)
{
    if (this==&other)
        return ;
    
    data_=other.data_;
    main_chain_=other.main_chain_;
    pend_=other.pend_;
    idx_pair_=other.idx_pair_;

    return (*this);
}

FordJohnson::~FordJohnson() {}

// In main_chain, search the IdxValue object its idx variable has unique_idx given as an argument.
IdxValue FordJohnson::getIdxValueOf(int unique_idx)
{
    std::deque<IdxValue>::const_iterator it = main_chain_.begin();
    std::deque<IdxValue>::const_iterator end_it = main_chain_.end();

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

int      FordJohnson::getPositionOf(int unique_idx)
{
    std::deque<IdxValue>::const_iterator it = main_chain_.begin();
    std::deque<IdxValue>::const_iterator end_it = main_chain_.end();

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

void FordJohnson::Paring()
{
    // data をmain_chain, pend_chainに振り分ける。
    // split data into main_chain and pend keeping the idx of the values
    size_t size = data_.size()/2;
    size_t pair_idx = 0;
    size_t data_idx = 0;

    //元のデータに対するループ
    while (pair_idx<size)
    {
        IdxValue large_idx_value;
        IdxValue small_idx_value;
        int large_unique_idx = -1;
        int small_unique_idx = -1;

        // データ要素を比較し、データのオリジナルのインデックスをIdxPair構造体に格納する。
        if (data_[data_idx]<data_[data_idx+1])
        {
            large_idx_value = data_[data_idx+1];
            small_idx_value = data_[data_idx];
            large_unique_idx = data_[data_idx+1].unique_idx;
            small_unique_idx = data_[data_idx].unique_idx;
        }
        else
        {
            large_idx_value = data_[data_idx];
            small_idx_value = data_[data_idx+1];
            large_unique_idx = data_[data_idx].unique_idx;
            small_unique_idx = data_[data_idx+1].unique_idx;
        }
        main_chain_.push_back(large_idx_value);
        pend_.push_back(small_idx_value);
        idx_pair_.add(large_unique_idx, small_unique_idx);
        ++pair_idx;
        data_idx += 2;
    }
    // add remaining one
    if (data_.size()%2!=0)
    {
        pend_.push_back(data_.back());
        idx_pair_.add(REMAINING_ELEM, data_.back().unique_idx);
    }
}
