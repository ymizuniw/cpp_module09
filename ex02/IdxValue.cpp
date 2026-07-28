# include "IdxValue.hpp"

IdxValue::IdxValue(): unique_idx(-1), value(-1){}

IdxValue::IdxValue(const IdxValue &other)
{
    if (this==&other)
        return ;
    this->unique_idx = other.unique_idx;
    this->value = other.value;
}

IdxValue &IdxValue::operator=(const IdxValue &other)
{
    if (this==&other)
        return (*this);
    this->unique_idx = other.unique_idx;
    this->value = other.value;
    return (*this);
}

bool IdxValue::operator<(const IdxValue &other)
{
    if (this->value<other.value)
        return (true);
    return (false);
}
