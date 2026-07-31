#ifndef IDX_VALUE_HPP
#define IDX_VALUE_HPP

struct IdxValue {
    int unique_idx;
    int value;
    IdxValue();
    IdxValue(int unique_idx, int value);
    bool operator<(const IdxValue& other) const;
};

#endif
