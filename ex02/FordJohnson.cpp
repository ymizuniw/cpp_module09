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

void FordJohnson::sortPend()
{
    // sort pend data by the main_chain idx
   std::deque<IdxValue> sorted_pend;
   
   std::deque<IdxValue>::const_iterator it = main_chain_.begin();
    std::deque<IdxValue>::const_iterator end_it = main_chain_.end();
   int pend_unique_idx;

   while (it!=end_it)
   {
    pend_unique_idx = idx_pair_.getPendIdxOf((*it).unique_idx);
    sorted_pend.push_back(getIdxValueOfPend(pend_unique_idx));
    ++it;
   }
   if (pend_.size()%2!=0)
   {
    sorted_pend.push_back(pend_.back());
   }
   pend_ = sorted_pend;
}

// Insertion()
    // [y1, x1, x2, ..., xm]
    // [y2, y3, y4, ..., ym]

    // 上界を決めるxのインデックス番号　+ これまでに挿入した要素数 = 次の探索空間のサイズ
    //　2^k <= SpaceSize < 2^(k+1) で最大となるような、　上界を決めるxのインデックス番号を求める

    // 現在の k の値はどう定義されるか。
    // log2(上界として使用したxのインデックスより左側にあるSの要素数)　で求められる気がする。
    // それか、何回目のグループ分けかを記録しておく。
    // この時 k の初期値はいくつか。
    // k=0: 1 -> 比較回数は一回だが、先頭要素に対する比較は比較なしで決定されるため初項として不適。
    // k=1: 2 -> 比較回数は2回で、[y1,x1]の完成後にy2を挿入することを考えた時、適する。また、y3を挿入することを考えても、[y1,x1,x2]に対して2回の比較で挿入位置を得られる。

    // 仮に、挿入候補数がupper_idx_ceiling 未満の場合は、残存要素数を代わりに取る。
    // if (pendRemainSize<upper_idx_ceiling)
    //     upper_idx_ceiling = pendRemainSize;
    
    // main_chainにおけるindexの検索は、main_chainのデータ型であるIdxValueのidxを参照して、pend[i].idxと一致する要素の、main_chainにおける位置を検索する。

    // 1. [y1,x1]の完成後にy2を挿入することを考える
    //     ・y2に対する挿入インデックスの上界は、y2のペアx2のmain_chainにおけるインデックスである。
    //     ・まず、y2に対応するx2のインデックス値をidx_pairから検索して得る。インデックス値は最初に一意に割り当てられているので、必ず見つかる。
    //     ・得られたx2のインデックス値をキーとして、main_chainにおけるインデックス（位置）を取得する。
    //     ・y2の探索空間の上限を決めるmain_chainのインデックスは、この値になる。

    // pendの残存要素数を取得する方法は、
    // 最初にpendのサイズを変数に格納しておき、
    // 挿入を実行したらその変数をデクリメントする。

# include <iostream>
static void insertByJacobsthal(std::deque<IdxValue> &sorted_main_chain, std::deque<IdxValue> &sorted_pend)
{
    int k = 1;
    // int pend_idx = 1;
    std::deque<IdxValue>::const_iterator pend_it = sorted_pend.cbegin() + 1; // the second element
    std::deque<IdxValue>::const_iterator pend_end_it = sorted_pend.cend();

    // Insertion range iterator
    std::deque<IdxValue>::const_iterator start_it;
    std::deque<IdxValue>::const_iterator end_it;

    int inserted_count = 1; // first elem is inserted.
    int pend_size = sorted_pend.size();

    while (pend_it!=pend_end_it)
    {
        // int upper_size_floor = 2^k;
        int upper_size_ceiling = 2^k - 1;
        int space_size = inserted_count * 2;
        start_it = pend_it;

        if (pend_size<upper_size_ceiling)
            upper_size_ceiling = pend_size;
        while (1)
        {
            if (space_size<upper_size_ceiling)
            {
                ++pend_it;
                ++space_size;
                continue ;
            }
            break ;
        }
        end_it = pend_it - 1;

        // main_chain上の上界のイテレータ
        std::deque<IdxValue>::const_iterator main_chain_upper_it = sorted_main_chain.cbegin() - (space_size - 1);
        std::cout << "space_size: " << space_size << std::endl;
        while (start_it!=end_it)
        {
            std::deque<IdxValue>::const_iterator it = std::upper_bound(sorted_main_chain.cbegin(), main_chain_upper_it, (*start_it));
            sorted_main_chain.insert(it, (*start_it));
            ++inserted_count;
            ++start_it;
        }
    }
}

void FordJohnson::insertion()
{
    int main_chain_key = main_chain_[0].unique_idx;
    int pend_idx = idx_pair_.getPendIdxOf(main_chain_key);

    IdxValue pend_elem = getIdxValueOfPend(pend_idx);
    main_chain_.push_front(pend_elem);
    std::cout << "main_chan_[0] " << main_chain_[0].value << std::endl;
    std::cout << "main_chan_[1] " << main_chain_[1].value << std::endl;
    if (pend_.size()==1)
        return ;
    for (int i = 0;i<int(pend_.size());i++)
    {
        std::cout << "pend_[" << i << "] " << pend_[i].value << std::endl;
    }
    insertByJacobsthal(main_chain_, pend_);
}

int count = 0;
# include <iostream>
// meta logic
std::deque<IdxValue> FordJohnson::sort()
{

    std::cout << "count:" << count++ << std::endl;
    
    // for (int i=0;i<static_cast<int>(data_.size());i++)
    // {
    //     std::cout << " data[" << i << "]" << data_[i].value << std::endl;
    // }
    
    if (data_.size()==1)
    {
        // std::cout << "data_.size()==1" << std::endl;
        main_chain_.push_back(data_.back());
        // std::cout << "data_.back()=="<< main_chain_.back().value << std::endl;
        // for (int i=0;i<static_cast<int>(main_chain_.size());i++)
        // {
        //     std::cout << "main_chain["<<i<<"] " << main_chain_[i].value << std::endl;
        // }
        return (main_chain_);
    }
    pairing();
    FordJohnson recursive_fj(main_chain_);
    // std::cout << "here" << std::endl;
    main_chain_ = recursive_fj.sort();
    // for (int i=0;i<static_cast<int>(main_chain_.size());i++)
    // {
    //     std::cout << "main_chain["<<i<<"] " << main_chain_[i].value << std::endl;
    // }
    sortPend();

    // std::cout << pend_[0].value << std::endl;
    insertion();
    // std::cout << main_chain_[0].value << std::endl;
    return (main_chain_);
}
