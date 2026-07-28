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

// // Orthodox canonical form 
// FordJohnson::FordJohnson(std::deque<IdxValue> num) {
// }

void InsertByJacobsthal(std::deque<IdxValue> &sorted_main_chain, std::deque<IdxValue> &pend, std::deque<IdxPair> &idx_pair)
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
    
    // main_chainにおけるindexの検索は、main_chainのデータ型であるIdxValueのidxを参照して、pend[i].idxと一致する要素の、main_chainにおける位置を検索する。

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
            int x_IdxValue_idx = search_pair_idx(idx_pair, pend[pend_idx].idx, false);
            int x_main_idx = get_idx_by_IdxValue_idx(sorted_main_chain, x_IdxValue_idx);
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
            // pend[tmp_end] に対応するsorted_main_chainのインデックスを上限にして、
            // sorted_main_chain を二分探索してpend[tmp_end]の挿入箇所を取得する。
            // 取得した挿入箇所に挿入する。
            //　pend_size--;

            // sorted_main_chainの範囲指定イテレータは、std::deque<IdxValude>::const_iterator型で取得可能
            // 
            // -> upper_bound(start, end, target, comp_func);
            // deque で利用可能なinsert関数を使用してIdxValueを挿入する。

            tmp_end--;
        }
        pend_idx_start = pend_idx;// for the next loop
    }

}

void Insertion(std::deque<IdxValue> &sorted_main_chain, std::deque<IdxValue> &pend, std::deque<IdxPair> &idx_pair)
{
    // here, pend elements would be inserted into sorted_main_chain, 
    // but the idx_pair can be lacking for the last element in pend,
    // and the element cannot be searched by the upper limit of the corresponding element in the sorted_main_chain

    bool odd = (pend.size()%2!=0);

    // 1. Insert the pend_element of the smallest element in the sorted_main_chain
    int main_chain_key = sorted_main_chain[0].idx;
    int pend_idx = search_pair_idx(idx_pair, main_chain_key, false);
    if (pend_idx==-1)
        throw std::runtime_error("Invalid Key");
    IdxValue pend_val = get_elem_by_idx(pend, pend_idx);
    if (pend_val.idx==-1)
        throw std::runtime_error("Invalid Value");
    sorted_main_chain.push_front(pend_val);

    // 2. Insert by the Jacobsthal
    // S = [y1, x1, x2, ..., xm]
    // P = [y2, y3, y4, ..., ym]


}

std::deque<IdxValue> FordJohnson(std::deque<IdxValue> const &data)
{
    std::deque<IdxValue> main_chain;
    std::deque<IdxValue> pend;
    std::deque<IdxPair> idx_pair;

    // keep remaining data if odd ocunt
    IdxValue remain = IdxValue();
    if (data.size()%2!=0)
    {
        remain = data[data.size()-1];
    }

    // Pairing()
    Paring(data, main_chain, pend, idx_pair);

    std::deque<IdxValue> sorted_main_chain = FordJohnson(main_chain);

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
