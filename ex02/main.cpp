#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <deque>

/*
    PROGRAM: PmergeMe
    INPUT:  ./PmergeMe 3 5 9 7 4
    DATA STRUCTURE: std::deque<int>
    LOGIC:
        
*/ 

/*
    map<int, int> : index and value
    1. sort the larger group recursively
    2. insert the smallest pair's partner by serching the partner's index in the map
    3. incert the remaining elements in the order of Jacobsthal numbers by binary search in the sorted larger group.
*/

struct Dict{
    int idx;
    int value;
    Dict();
    Dict(const Dict &other);
    Dict &operator=(const Dict &other);
    bool operator<(const Dict &other) const;
    bool operator<(const Dict &other);
};

struct IdxPair{
    int main_chain_idx;
    int pend_idx;
    IdxPair();
    IdxPair(const Dict &other);
    IdxPair &operator=(const IdxPair &other);
};

Dict::Dict(): idx(-1), value(-1){}

Dict::Dict(const Dict &other): idx(other.idx), value(other.value)
{
    if (this==&other)
        return ;
    this->idx = other.idx;
    this->value = other.value;
}

Dict &Dict::operator=(const Dict &other)
{
    if (this==&other)
        return (*this);
    this->idx = other.idx;
    this->value = other.value;
    return (*this);
}

bool Dict::operator<(const Dict &other) const
{
    if (this->value<other.value)
        return (true);
    return (false);
}

bool Dict::operator<(const Dict &other)
{
    if (this->value<other.value)
        return (true);
    return (false);
}

void Paring(std::deque<Dict> const &data, std::deque<Dict> &main_chain, std::deque<Dict> &pend, std::deque<IdxPair> &idx_pair)
{
    // split data into main_chain and pend keeping the idx of the values
    size_t size = data.size()/2;

    size_t pair_idx = 0;
    size_t data_idx = 0;
    Dict large_value = Dict();
    Dict pend_value = Dict();
    IdxPair idx_pair_tmp = IdxPair();

    while (pair_idx<size)
    {
        if (data[data_idx]<data[data_idx+1])
        {
            large_value = data[data_idx+1];
            pend_value = data[data_idx];
            idx_pair_tmp.main_chain_idx = data[data_idx+1].idx;
            idx_pair_tmp.pend_idx = data[data_idx].idx;
        }
        else
        {
            large_value = data[data_idx];
            pend_value = data[data_idx+1];
            idx_pair_tmp.main_chain_idx = data[data_idx].idx;
            idx_pair_tmp.pend_idx = data[data_idx+1].idx;
        }
        main_chain.push_back(large_value);
        pend.push_back(pend_value);
        idx_pair.push_back(idx_pair_tmp);
        ++pair_idx;
        data_idx += 2;
    }
}

// if target_is_pend=true, then search by key in main_chain_idx and return the pend_idx,
// else in pend_idx and return main_chain_idx
int search_pair_idx(std::deque<IdxPair> const &idx_pair, int key, bool target_is_pend)
{
    std::deque<IdxPair>::const_iterator it = idx_pair.begin();
    std::deque<IdxPair>::const_iterator end_it = idx_pair.end();

    while (it!=end_it)
    {
        if (target_is_pend)
        {
            if ((*it).main_chain_idx==key)
                return ((*it).pend_idx);
        }
        else
        {
            if ((*it).pend_idx==key)
                return ((*it).main_chain_idx);     
        }
        ++it;
    }
    return (-1);
}

// int x_main_idx = // search idx of the element its idx is key, from main_chain
int get_idx_by_dict_idx(std::deque<Dict> &chain, int dict_idx)
{
    std::deque<Dict>::const_iterator it = chain.begin();
    std::deque<Dict>::const_iterator end_it = chain.end();

    int idx = 0;
    while (it!=end_it)
    {
        if ((*it).idx==dict_idx)
            return (idx);
        ++idx;
        ++it;
    }
    return (-1);
}

Dict get_value_by_idx(std::deque<Dict> &chain, int idx)
{
    std::deque<Dict>::const_iterator it = chain.begin();
    std::deque<Dict>::const_iterator end_it = chain.end();

    while (it!=end_it)
    {
        if ((*it).idx==idx)
            return ((*it));
        ++it;
    }
    return (Dict());// not so good
}

void InsertByJacobsthal(std::deque<Dict> &sorted_main_chain, std::deque<Dict> &pend, std::deque<IdxPair> &idx_pair)
{
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
    
    // main_chainにおけるindexの検索は、main_chainのデータ型であるDictのidxを参照して、pend[i].idxと一致する要素の、main_chainにおける位置を検索する。

    // 1. [y1,x1]の完成後にy2を挿入することを考える
    //     ・y2に対する挿入インデックスの上界は、y2のペアx2のmain_chainにおけるインデックスである。
    //     ・まず、y2に対応するx2のインデックス値をidx_pairから検索して得る。インデックス値は最初に一意に割り当てられているので、必ず見つかる。
    //     ・得られたx2のインデックス値をキーとして、main_chainにおけるインデックス（位置）を取得する。
    //     ・y2の探索空間の上限を決めるmain_chainのインデックスは、この値になる。

    int k = 1;
    int pend_idx = 0;
    int size_pend = pend.size();
    int pend_idx_start = 0;
    int pend_idx_end = 0;

    while ()
    {
        int upper_size_floor = 2^k;
        int upper_size_ceiling = 2^k - 1;

        // pendの残存要素数を取得する方法は、
        // 最初にpendのサイズを変数に格納しておき、
        // 挿入を実行したらその変数をデクリメントする。
        if (size_pend<upper_size_ceiling)
            upper_size_ceiling = size_pend;
        while (1)
        {
            int x_dict_idx = search_pair_idx(idx_pair, pend[pend_idx].idx, false);
            int x_main_idx = get_idx_by_dict_idx(sorted_main_chain, x_dict_idx);
            int space_size = x_main_idx + 1;

            if (space_size<upper_size_ceiling)
            {
                // pendの挿入候補をまだ増やせる（かも）
                pend_idx++;
                continue ;
            }
            break ;
        }
        pend_idx_end = pend_idx - 1; // for the current loop

        // InsertGroup()
        // decrement the size of group : size_pend
        // range: sorted_main_chain[0] ~ sorted_main_chain[x_main_idx]
        int tmp_end = pend_idx_end;
        while (tmp_end>pend_idx_start)
        {
            // insert pend[tmp_end] to sorted_main_chain
            // sorted_main_chain を二分探索してpend[tmp_end]の挿入箇所を取得する。
            // 取得した挿入箇所に挿入する。
            //　pend_size--;
            tmp_end--;
        }
        pend_idx_start = pend_idx;// for the next loop
    }

}

void Insertion(std::deque<Dict> &sorted_main_chain, std::deque<Dict> &pend, std::deque<IdxPair> &idx_pair)
{
    // here, pend elements would be inserted into sorted_main_chain, 
    // but the idx_pair can be lacking for the last element in pend,
    // and the element cannot be searched by the upper limit of the corresponding element in the sorted_main_chain

    bool odd = (pend.size()%2!=0);

    // 1. Insert the pend_element of the smallest element in the sorted_main_chain
    int main_chain_key = sorted_main_chain[0].idx;
    int pend_idx = search_pend_idx_by_main_chain_key(idx_pair, main_chain_key);
    if (pend_idx==-1)
        throw std::runtime_error("Invalid Key");
    Dict pend_val = get_value_by_idx(pend, pend_idx);
    if (pend_val.idx==-1)
        throw std::runtime_error("Invalid Value");
    sorted_main_chain.push_front(pend_val);

    // 2. Insert by the Jacobsthal
    // S = [y1, x1, x2, ..., xm]
    // P = [y2, y3, y4, ..., ym]


}

std::deque<Dict> FordJohnson(std::deque<Dict> const &data)
{
    std::deque<Dict> main_chain;
    std::deque<Dict> pend;
    std::deque<IdxPair> idx_pair;

    // keep remaining data if odd ocunt
    Dict remain = Dict();
    if (data.size()%2!=0)
    {
        remain = data[data.size()-1];
    }

    // Pairing()
    Paring(data, main_chain, pend, idx_pair);

    std::deque<Dict> sorted_main_chain = FordJohnson(main_chain);

    if (data.size()%2!=0)
    {
        pend.push_back(remain);
    }

    // Insertion()

    return (sorted_main_chain);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <list of integers>" << std::endl;
        return (1);
    }

    int tmp[argc - 1];
    for (int i = 1; i < argc; ++i)
    {
        tmp[i - 1] = 0;
    }
    for (int i = 1; i < argc; ++i)
    {
        tmp[i - 1] = std::atoi(argv[i]);
    }

    return (0);
}
