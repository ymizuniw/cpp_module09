# include "FordJohnson.hpp"

FordJohnson::FordJohnson(): idx_pair_() {}

FordJohnson::FordJohnson(std::deque<IdxValue> const &data)
{
    data_=data;
}

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
        return (*this);
    
    data_=other.data_;
    main_chain_=other.main_chain_;
    pend_=other.pend_;
    idx_pair_=other.idx_pair_;

    return (*this);
}

FordJohnson::~FordJohnson() {}

// In main_chain, search the IdxValue object its idx variable has unique_idx given as an argument.
IdxValue FordJohnson::getIdxValueOfMainChain(int unique_idx)
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

// In pend, search the IdxValue object its idx variable has unique_idx given as an argument.
IdxValue FordJohnson::getIdxValueOfPend(int unique_idx)
{
    std::deque<IdxValue>::const_iterator it = pend_.begin();
    std::deque<IdxValue>::const_iterator end_it = pend_.end();

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

int      FordJohnson::getPositionOfMainChain(int unique_idx)
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

void FordJohnson::pairing()
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
        int large_idx = -1;
        int small_idx = -1;

        // データ要素を比較し、データのオリジナルのインデックスをIdxPair構造体に格納する。
        if (data_[data_idx]<data_[data_idx+1])
        {
            large_idx_value = data_[data_idx+1];
            small_idx_value = data_[data_idx];
            large_idx = data_[data_idx+1].unique_idx;
            small_idx = data_[data_idx].unique_idx;
        }
        else
        {
            large_idx_value = data_[data_idx];
            small_idx_value = data_[data_idx+1];
            large_idx = data_[data_idx].unique_idx;
            small_idx = data_[data_idx+1].unique_idx;
        }
        main_chain_.push_back(large_idx_value);
        pend_.push_back(small_idx_value);
        idx_pair_.add(large_idx, small_idx);
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

void FordJohnson::sortPend()
{
    // sort pend data by the main_chain idx
    std::deque<IdxValue> new_pend;
   
    std::deque<IdxValue>::const_iterator it = main_chain_.begin();
    std::deque<IdxValue>::const_iterator end_it = main_chain_.end();
   int pend_unique_idx;

   while (it!=end_it)
   {
    pend_unique_idx = idx_pair_.getSmallIdxOf((*it).unique_idx);
    new_pend.push_back(getIdxValueOfPend(pend_unique_idx));
    ++it;
   }
   if (data_.size()%2!=0)
   {
    new_pend.push_back(pend_.back());
   }
   pend_ = new_pend;
}

int FordJohnson::getSpaceSize(std::deque<IdxValue>::const_iterator &pend_it)
{
    int pos = idx_pair_.getLargeIdxOf((*pend_it).unique_idx);
    if (pos==REMAINING_ELEM)
        return (main_chain_.size());
    return (getPositionOfMainChain(pos)+1);
}

void FordJohnson::insertByJacobsthal()
{
    int k = 1;
    std::deque<IdxValue>::const_iterator pend_it = pend_.cbegin() + 1; // the second element
    std::deque<IdxValue>::const_iterator pend_end_it = pend_.cend();

    std::deque<IdxValue>::const_iterator start_it;
    std::deque<IdxValue>::const_iterator end_it;

    while (pend_it!=pend_end_it)
    {
        int upper_size_ceiling = (1<<k) - 1;
        int space_size = getSpaceSize(pend_it);
        start_it = pend_it;

        while (space_size<upper_size_ceiling)
        {
            ++pend_it;
            if (pend_it==pend_end_it)
                break ;
            space_size = getSpaceSize(pend_it);
        }
        if (pend_it!=pend_end_it)
            ++pend_it;
        end_it = pend_it;
        // main_chain上の上界のイテレータ
        std::deque<IdxValue>::const_iterator main_chain_upper_it = main_chain_.cbegin() + space_size;
        while (start_it!=end_it)
        {
            std::deque<IdxValue>::const_iterator it = std::upper_bound(main_chain_.cbegin(), main_chain_upper_it, (*end_it));
            main_chain_.insert(it, (*end_it));
            --end_it;
        }
        ++k;
    }
}

void FordJohnson::insertion()
{
    int main_chain_key = main_chain_[0].unique_idx;
    int pend_idx = idx_pair_.getSmallIdxOf(main_chain_key);

    IdxValue pend_elem = getIdxValueOfPend(pend_idx);
    main_chain_.push_front(pend_elem);
    if (pend_.size()==1)
        return ;
    insertByJacobsthal();
}

std::deque<IdxValue> FordJohnson::sort()
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
