## C++98 で使用可能なコンテナ

**シーケンスコンテナ**
- `std::vector`
- `std::deque`
- `std::list`

**連想コンテナ**
- `std::set`
- `std::multiset`
- `std::map`
- `std::multimap`

# Merge-Insertion Sort (Ford–Johnson Algorithm)

Merge-insertion sort performs the following steps on an input $X$ of $n$ elements:[6]

1. **Pair up elements.** Group the elements of `X` into `⌊n/2⌋` pairs, arbitrarily, leaving one element unpaired if `n` is odd.

2. **Compare each pair.** Perform `⌊n/2⌋` comparisons, one per pair, to determine the larger element of each pair.

3. **Recursively sort the larger elements.** Recursively sort the `⌊n/2⌋` "larger" elements using merge-insertion sort, producing a sorted sequence `S` of `⌊n/2⌋` elements in ascending order.

4. **Insert the smallest pair's partner.** Insert, at the start of `S`, the element that was paired with the first (smallest) element of `S`.

5. **Insert the remaining elements.** Insert the remaining `⌈n/2⌉ − 1` elements of `X ∖ S` into `S`, one at a time, using a specially chosen insertion order (described below). For each insertion, use [binary search](https://en.wikipedia.org/wiki/Binary_search) within the appropriate subsequence of `S` to determine the correct position.

- we know that the bound for bx is ax. So when we insert, for example b5 instead of searching in {b1, a1, b2, a2, b3, a3, a4, a5, a6, a7, ...} we can search in {b1, a1, b2, a2, b3, a3, a4}, because we know that there is no point to include into the search range a5 and anything after that since they are guarenteed to be bigger. After we inserted b5 and it is time to insert b4, the bound is decreased by one (from a5 to a4), but the amount of elements is increased by one (we inserted b5), so the amount of elements in this range stayed the same.
- https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91

