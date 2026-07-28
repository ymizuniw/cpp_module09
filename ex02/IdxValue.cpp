# include "IdxValue.hpp"

IdxValue::IdxValue(): unique_idx(-1), value(-1){}

IdxValue::IdxValue(int unique_idx, int value): unique_idx(unique_idx), value(value){}

bool IdxValue::operator<(const IdxValue &other)
{
    if (this->value<other.value)
        return (true);
    return (false);
}
